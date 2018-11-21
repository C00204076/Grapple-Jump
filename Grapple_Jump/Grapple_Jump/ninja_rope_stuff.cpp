//copied from player.h and player.cpp

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

float rope_px, rope_py;//rope offset from player position

	Map				*rope_map;
	Sprite			*sprite_rope;
	Sprite			*sprite_slider;
	Sprite			*sprite_rotor;
	EntityJoint		*rope;
	EntityJoint		*rope_revolute_i;
	ParticleEffect	*rope_effect;

	

	int		rope_type;
	float	rope_length;

	//konop se tokom zivota u biti moze sudarit samo s JEDNIM spriteom, i onda se razdvoji i napravi se drui sprite
	std::vector<Vector3>	rope_points;//global position and speed/direction
	//local point for rotating terrain
	std::vector<Sprite*>	rope_sprites;
	std::vector<b2Vec2>		rope_sprites_vertices;//local position on the body

	//tmp collision data
	std::vector<Vector3>	rope_breakpoints;
	Sprite *rope_break;
	std::vector<b2Fixture*>	begin_fixtures;
	
	//raycast
	b2Body* ShootRope(b2Vec2 &intersectionPoint, b2Vec2 &intersectionNormal);
	
	void	UpdateRope(Map *map);

	void	MakeRope_Joint(Map *map);
	void	RemoveRope_Joint();

	void	MakeRope_Chain(Map *map);	
	void	RemoveRope_Chain();
	
	//simple or ninja rope with wrapping
	void	MakeRope_Prismatic(bool simple, float ix, float iy, Sprite *target, Sprite *player, Map *map, bool add_point, float speed);
	bool	UpdateRope_Prismatic(bool simple, Map *map);			
	bool	Rope_Reconnect(Map *map);
	void	RemoveRope_Prismatic(bool objects, bool rest, bool collisions, bool sprites);

	void	Rope_BeginContact(b2Contact *contact, b2Fixture *fa, b2Fixture *fb);
	void	Rope_PreSolve(b2Contact *contact, const b2Manifold *oldManifold, b2Fixture *fa, b2Fixture *fb);	

	void	CollisionPointToVertex(float &xx, float &yy, Sprite *a);
	void	AddRopeEffect(float sx, float sy, float ex, float ey, Sprite *sprite);
	
////////// NINJA ROPE
//////////

void Player::UpdateRope(Map *map)
{
//change rope type
	if(this->engine->input->GetKeyR(SDLK_r))
	{
		if(this->rope_type==-1)			this->RemoveRope_Joint();
		else if(this->rope_type==0)		this->RemoveRope_Joint();
		else if(this->rope_type==1)		this->RemoveRope_Chain();
		else this->RemoveRope_Prismatic(true,true,true,true);

		this->rope_type++;
		if(this->rope_type>3) this->rope_type = -1;
	}

	if(this->rope_type==-1)		this->MakeRope_Joint(map);
	else if(this->rope_type==0)	this->MakeRope_Joint(map);
	else if(this->rope_type==1) this->MakeRope_Chain(map);
	else if(this->rope_type==2) this->UpdateRope_Prismatic(true,map);
	else if(this->rope_type==3) this->UpdateRope_Prismatic(false,map);
	
	//update rope effect to render line
	if(this->rope_effect)
	{
		float rpx = this->p_player->getBone("arm2_down")->GetAttpX(0);
		float rpy = this->p_player->getBone("arm2_down")->GetAttpY(0);

		ParticleEffect *ef = this->rope_effect;
		for(std::list<ParticleEmitter*>::iterator l=ef->emitters.begin();l!=ef->emitters.end();l++)
		{
			ParticleEmitter *em = *l;
			if(em->beam_type!=PE_NULL && em->shape)
			{
				//first point, will crash if sprite is deleted
				em->shape->vs[0].SetP(
					this->rope_sprites[0]->GetBody()->GetWorldPoint(this->rope_sprites_vertices[0]).x*map->m2p,
					this->rope_sprites[0]->GetBody()->GetWorldPoint(this->rope_sprites_vertices[0]).y*map->m2p);
				em->shape->tf[0].SetP(em->shape->vs[0].p.GetX(),em->shape->vs[0].p.GetY());

				//last point is player position
				em->shape->vs[em->shape->vs.size()-1].SetP(rpx,rpy);
				em->shape->tf[em->shape->tf.size()-1].SetP(rpx,rpy);
			}
		}
	}
	
	//clear break points in this frame
	this->begin_fixtures.clear();
	this->rope_breakpoints.clear();
	this->rope_break = NULL;			
}

//raycast to initialy attach the rope to terrain
b2Body* Player::ShootRope(b2Vec2 &intersectionPoint, b2Vec2 &intersectionNormal)
{
	float rpx = this->p_player->GetX() + this->rope_px;
	float rpy = this->p_player->GetY() + this->rope_py;

	float angle = _AngleToTarget(rpx,rpy,this->cx,this->cy);

	b2Vec2 p1(rpx*map->p2m,rpy*map->p2m);
	b2Vec2 p2((rpx + cos(angle)*this->rope_length)*map->p2m,(rpy + sin(angle)*this->rope_length)*map->p2m);

	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1;

	b2Body *target = NULL;
	b2Fixture *tf = NULL;

	//CHANGE TO USE WORLD QUERY !!!

	//check every fixture of every body to find closest
	float closestFraction = 1; //start with end of line as p2	

	for(b2Body *b=map->world->GetBodyList();b;b=b->GetNext())
	{
		if(b->GetType()==b2_staticBody || b->GetType()==b2_kinematicBody)
			for(b2Fixture *f=b->GetFixtureList();f;f=f->GetNext())
			{
				b2RayCastOutput output;
				if(f->GetType()==3)//chain
				{
					//child index edge od chain shape, svaki put po jednu liniju radi
					for(int i=0;i<f->GetShape()->GetChildCount();i++)
					{
						if(f->RayCast(&output,input,i))
							if(output.fraction < closestFraction)
							{
								target = b;
								tf = f;
								closestFraction = output.fraction;
								intersectionNormal = output.normal;
							}
					}
				}
				else
				{
					if(f->RayCast(&output,input,0))
						if(output.fraction < closestFraction)
						{
							target = b;
							tf = f;
							closestFraction = output.fraction;
							intersectionNormal = output.normal;
						}
				}
			}
	}

	if(!target || !target->GetUserData()) return NULL;

	intersectionPoint = p1 + closestFraction*(p2-p1);

	return target;
}


void Player::MakeRope_Joint(Map *map)
{
	//rope or distance joint method

	//move up/down
	if(this->engine->input->GetKey(SDLK_w))
	{
		if(this->rope)
		{
			if(this->rope_type==0)
			{
				b2RopeJoint *rj = (b2RopeJoint*)(this->rope->joint);
				rj->SetMaxLength(rj->GetMaxLength()-4*map->p2m);
			}
			else if(this->rope_type==-1)
			{
				b2DistanceJoint *dj = (b2DistanceJoint*)(this->rope->joint);
				dj->SetLength(dj->GetLength()-4*map->p2m);
			}
		}
	}
	else if(this->engine->input->GetKey(SDLK_s))
	{
		if(this->rope)
		{
			if(this->rope_type==0)
			{
				b2RopeJoint *rj = (b2RopeJoint*)(this->rope->joint);
				rj->SetMaxLength(rj->GetMaxLength()+4*map->p2m);
			}
			else if(this->rope_type==-1)
			{
				b2DistanceJoint *dj = (b2DistanceJoint*)(this->rope->joint);
				dj->SetLength(dj->GetLength()+4*map->p2m);
			}
		}
	}

	if(this->engine->input->GetMsBttnR(3))
	{
		//rope position on player
		float rpx = this->p_player->GetX() + this->rope_px;
		float rpy = this->p_player->GetY() + this->rope_py;

		//remove existing rope
		if(this->rope)
		{
			this->RemoveRope_Joint();
			return;
		}

		//create new rope
		b2Vec2 intersectionPoint, intersectionNormal;
		b2Body *target = this->ShootRope(intersectionPoint,intersectionNormal);
		if(!target) return;

		this->rope = new EntityJoint();

		if(this->rope_type==0)
		{
			this->rope->type = e_ropeJoint;		
			this->rope->jd_rp.maxLength = _Distance(rpx*map->p2m,rpy*map->p2m,intersectionPoint.x,intersectionPoint.y);
			this->rope->jd_rp.collideConnected = true;

			this->rope->a = this->p_player;
			this->rope->jd_rp.bodyA = this->p_player->GetBody();
			this->rope->jd_rp.localAnchorA = b2Vec2(this->p_player->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

			this->rope->b = target->GetUserData();
			this->rope->jd_rp.bodyB = target;
			this->rope->jd_rp.localAnchorB = b2Vec2(target->GetLocalPoint(intersectionPoint));

			this->rope->joint = map->world->CreateJoint(&this->rope->jd_rp);
			this->rope->joint->SetUserData(this->rope);
		}
		else if(this->rope_type==-1)
		{
			this->rope->type = e_distanceJoint;
			this->rope->jd_dist.length = _Distance(rpx*map->p2m,rpy*map->p2m,intersectionPoint.x,intersectionPoint.y);
			this->rope->jd_dist.collideConnected = true;

			this->rope->a = this->p_player;
			this->rope->jd_dist.bodyA = this->p_player->GetBody();
			this->rope->jd_dist.localAnchorA = b2Vec2(this->p_player->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

			this->rope->b = target->GetUserData();;
			this->rope->jd_dist.bodyB = target;
			this->rope->jd_dist.localAnchorB = b2Vec2(target->GetLocalPoint(intersectionPoint));

			this->rope->joint = map->world->CreateJoint(&this->rope->jd_dist);
			this->rope->joint->SetUserData(this->rope);
		}

		if(this->rope->joint)
		{
			((Sprite*)target->GetUserData())->AddJoint(this->rope);
			this->p_player->AddJoint(this->rope);
			this->rope->joint->SetUserData(this->rope);
			map->joints.push_back(this->rope);

			this->rope_points.push_back(Vector3(intersectionPoint.x*map->m2p,intersectionPoint.y*map->m2p,0));
			this->rope_sprites.push_back((Sprite*)target->GetUserData());
			this->rope_sprites_vertices.push_back(target->GetLocalPoint(intersectionPoint));

			this->AddRopeEffect(intersectionPoint.x*map->m2p,intersectionPoint.y*map->m2p,rpx,rpy,this->p_player);
		}
		else
		{
			delete this->rope;
			this->rope = NULL;
		}
	}

}

void Player::MakeRope_Prismatic(bool simple, float ix, float iy, Sprite *target, Sprite *player, Map *map, bool add_point, float speed)
{
	float rpx = this->p_player->GetX() + this->rope_px;
	float rpy = this->p_player->GetY() + this->rope_py;

	//load ninja rope object

	Map *rope_map = NULL;

	if(simple) rope_map = this->engine->skeletons.GetSkeleton("Q2D/Maps/ninja-rope-prism1.xml");
	else rope_map = this->engine->skeletons.GetSkeleton("Q2D/Maps/ninja-rope.xml");	

	if(!rope_map) return;
	rope_map = rope_map->Copy();

	//get individual ninja rope components
	Sprite *rope_sp = NULL, *slider_sp = NULL, *rotor_sp = NULL;

	for(unsigned int i=0;i<rope_map->layers.size();i++)
	{
		for(std::list<Sprite*>::iterator j=rope_map->layers[i]->sprites.begin();j!=rope_map->layers[i]->sprites.end();j++)
		{
			if((*j)->getText()=="rope")
			{
				rope_sp = *j;

				if(!simple)
				{
					//calculate rope length
					float length = 0;

					if(!this->rope_points.empty())
					{
						length += _Distance(
							this->rope_points[this->rope_points.size()-1].GetX(),this->rope_points[this->rope_points.size()-1].GetY(),
							ix,iy);

						if(this->rope_points.size()>1)
						{						
							for(unsigned int k=0;k<this->rope_points.size()-1;k++)
								length += _Distance(this->rope_points[k].GetX(),this->rope_points[k].GetY(),this->rope_points[k+1].GetX(),this->rope_points[k+1].GetY());
						}						

						//smanji
						rope_sp->GetShpB2D()->vs[1].p.SetX(this->rope_length-length);
						rope_sp->GetShpR()->vs[1].p.SetX(this->rope_length-length);

						(*rope_map->joints.begin())->jd_prism.upperTranslation = ((this->rope_length-50)-length)*map->p2m;
					}
				}
			}
			else if((*j)->getText()=="slider")	slider_sp = *j;
			else if((*j)->getText()=="rotor")	rotor_sp = *j;
		}
	}
	
	rope_map->SetDeleteAll(false);
	this->engine->skeletons.ms.Make_Bodies(rope_map,map);
	this->engine->skeletons.ms.Make_Joints(rope_map,map,true);
	rope_map->Connect_Stuff();		
	map->MoveEntitiesFrom(rope_map,true,NULL,player->getLayer());//ovako se nece sacuvat ako se mapa save-a (save_skip)

	if(!rope_sp || !slider_sp || !rotor_sp || !rope_sp->GetBody() || !slider_sp->GetBody() || !rotor_sp->GetBody())
	{
		rope_map->SetAlive_Entities(false);
		delete rope_map;
		return;
	}	

	//tmp da se ne sudara sa feet senzorom igraca
	rope_sp->GetBody()->GetFixtureList()->SetFilterData(this->engine->collisions.GetCollisionFilter("debris")->filter);
	slider_sp->GetBody()->GetFixtureList()->SetFilterData(this->engine->collisions.GetCollisionFilter("debris")->filter);
	rotor_sp->GetBody()->GetFixtureList()->SetFilterData(this->engine->collisions.GetCollisionFilter("debris")->filter);

	//set rope sprite at intersection point and attach to body using revolute joint
	float angle = _AngleToTarget(ix,iy,rpx,rpy);
	
	rope_sp->SetPosition(ix,iy);	
	rope_sp->SetRotR(angle);
	rope_sp->GetBody()->SetTransform(b2Vec2(ix*map->p2m,iy*map->p2m),angle);

	//set slider and rotor to player position
	slider_sp->SetPosition(rpx,rpy);
	slider_sp->GetBody()->SetTransform(b2Vec2(rpx*map->p2m,rpy*map->p2m),angle);
	rotor_sp->SetPosition(rpx,rpy);
	rotor_sp->GetBody()->SetTransform(b2Vec2(rpx*map->p2m,rpy*map->p2m),angle);

	//connect rope to terrain on intersection point
	EntityJoint *ij = new EntityJoint();

	ij->type = e_revoluteJoint;		
	ij->jd_rev.collideConnected = true;

	ij->a = rope_sp;		
	ij->jd_rev.bodyA = rope_sp->GetBody();
	ij->jd_rev.localAnchorA = b2Vec2(0,0);

	ij->b = target;
	ij->jd_rev.bodyB = target->GetBody();
	ij->jd_rev.localAnchorB = b2Vec2(target->GetBody()->GetLocalPoint(b2Vec2(ix*map->p2m,iy*map->p2m)));

	ij->joint = map->world->CreateJoint(&ij->jd_rev);
	ij->joint->SetUserData(ij);

	if(!ij->joint)
	{
		delete ij;
		rope_map->SetAlive_Entities(false);
		delete rope_map;
		return;
	}	

	rope_sp->AddJoint(ij);
	target->AddJoint(ij);
	map->joints.push_back(ij);
	rope_map->joints.push_back(ij);//da mogu sve odjednom stavit alive=false

	//attach player to rotor, create player joint -  note rope and slider were already connected when the object was loaded
	EntityJoint *pj = new EntityJoint();

	pj->type = e_revoluteJoint;		
	pj->jd_rev.collideConnected = false;

	pj->a = rotor_sp;
	pj->jd_rev.bodyA = rotor_sp->GetBody();
	pj->jd_rev.localAnchorA = b2Vec2(0,0);

	pj->b = player;
	pj->jd_rev.bodyB = player->GetBody();
	pj->jd_rev.localAnchorB = b2Vec2(this->p_player->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

	pj->joint = map->world->CreateJoint(&pj->jd_rev);
	pj->joint->SetUserData(pj);

	if(!pj->joint)
	{
		delete pj;
		rope_map->SetAlive_Entities(false);
		delete rope_map;
		return;
	}

	rotor_sp->AddJoint(pj);
	player->AddJoint(pj);
	map->joints.push_back(pj);
	rope_map->joints.push_back(pj);//da mogu sve odjednom stavit alive=false

	//
	this->rope_map = rope_map;
	this->rope = *rope_map->joints.begin();
	this->rope_revolute_i = ij;

	rope_sp->GetShpR()->Transform();
	slider_sp->GetShpR()->Transform();
	rotor_sp->GetShpR()->Transform();

	if(add_point)
	{
		this->rope_points.push_back(Vector3(ix,iy,0));//speed is set outside as "z"
		this->rope_sprites.push_back(target);
		this->rope_sprites_vertices.push_back(target->GetBody()->GetLocalPoint(b2Vec2(ix*map->p2m,iy*map->p2m)));
	}

	//set rope speed to match the player if new, or use the speed of existing rope that will be removed
	if(this->sprite_rope && this->sprite_slider && this->sprite_rotor)
	{
		rope_sp->GetBody()->SetLinearVelocity(this->sprite_rope->GetBody()->GetLinearVelocity());
		rope_sp->GetBody()->SetAngularVelocity(this->sprite_rope->GetBody()->GetAngularVelocity());
		slider_sp->GetBody()->SetLinearVelocity(this->sprite_slider->GetBody()->GetLinearVelocity());
		slider_sp->GetBody()->SetAngularVelocity(this->sprite_slider->GetBody()->GetAngularVelocity());
		rotor_sp->GetBody()->SetLinearVelocity(this->sprite_rotor->GetBody()->GetLinearVelocity());
		rotor_sp->GetBody()->SetAngularVelocity(this->sprite_rotor->GetBody()->GetAngularVelocity());
	}
	else
	{
		rope_sp->GetBody()->SetLinearVelocity(this->p_player->GetBody()->GetLinearVelocity());
		rope_sp->GetBody()->SetAngularVelocity(this->p_player->GetBody()->GetAngularVelocity());
		slider_sp->GetBody()->SetLinearVelocity(this->p_player->GetBody()->GetLinearVelocity());
		slider_sp->GetBody()->SetAngularVelocity(this->p_player->GetBody()->GetAngularVelocity());
		rotor_sp->GetBody()->SetLinearVelocity(this->p_player->GetBody()->GetLinearVelocity());
		rotor_sp->GetBody()->SetAngularVelocity(this->p_player->GetBody()->GetAngularVelocity());
	}

	this->sprite_rope = rope_sp;
	this->sprite_slider = slider_sp;
	this->sprite_rotor = rotor_sp;	

	this->AddRopeEffect(ix,iy,rpx,rpy,player);
}

void Player::MakeRope_Chain(Map *map)
{
	if(this->engine->input->GetMsBttnR(3))
	{
		if(this->rope_map)
		{
			this->RemoveRope_Chain();			
			return;
		}

		float rpx = this->p_player->GetX() + this->rope_px;
		float rpy = this->p_player->GetY() + this->rope_py;

		//get point to attach to
		b2Vec2 intersectionPoint, intersectionNormal;
		b2Body *target_b = this->ShootRope(intersectionPoint,intersectionNormal);
		if(!target_b) return;

		/////
		float ix = intersectionPoint.x*map->m2p + intersectionNormal.x*5;
		float iy = intersectionPoint.y*map->m2p + intersectionNormal.y*5;
		Sprite *target = (Sprite*)target_b->GetUserData();
		Sprite *player = this->p_player;
		/////

		//load ninja rope object

		Map *rope_map = this->engine->skeletons.GetSkeleton("Q2D/Maps/ninja-rope-chain.xml");

		if(!rope_map) return;	

		//get copies of individual ninja rope components as templates
		Sprite *chain_sp = NULL;
		EntityJoint *link_j = NULL;

		for(unsigned int i=0;i<rope_map->layers.size();i++)
		{
			for(std::list<Sprite*>::iterator j=rope_map->layers[i]->sprites.begin();j!=rope_map->layers[i]->sprites.end();j++)
				if((*j)->getText()=="chain") chain_sp = (*j)->Copy();
		}

		for(std::list<EntityJoint*>::iterator j=rope_map->joints.begin();j!=rope_map->joints.end();j++)
			if(*j) link_j = (*j)->Copy();

		if(!chain_sp || !link_j) return;

		rope_map = new Map();
		rope_map->SetDeleteAll(false);
		rope_map->AddSpriteLayer(1);

		//length of one chain element, distance to player
		float length = _Distance(chain_sp->GetX(),chain_sp->GetY(),chain_sp->GetAttpX(0),chain_sp->GetAttpY(0));
		float dist = _Distance(ix,iy,rpx,rpy);
		float angle = _AngleToTarget(ix,iy,rpx,rpy);

		std::vector<Sprite*> chain;//contains individual links

		//from intersection point towards player add links
		for(unsigned int i=0;i<(int)dist/length;i++)
		{
			Sprite *chain_new = chain_sp->Copy();		

			float x = _TransformX(i*length,0,ix,iy,angle);
			float y = _TransformY(i*length,0,ix,iy,angle);

			//b2d body creation is based on these values
			chain_new->SetPosition(x,y);	
			chain_new->SetRotR(angle);
			chain_new->GetShpR()->Transform();

			rope_map->AddSprite(chain_new,(unsigned int)0);
			chain.push_back(chain_new);
		}

		//create bodies, so we can make joints
		this->engine->skeletons.ms.Make_Bodies(rope_map,map);

		Sprite *chain_last = target;

		//create joints between links
		for(unsigned int i=0;i<chain.size()-1;i++)	
		{
			Sprite *link = chain[i];
			Sprite *link_next = chain[i+1];

			link->GetBody()->GetFixtureList()->SetFilterData(this->engine->collisions.GetCollisionFilter("debris")->filter);
			link_next->GetBody()->GetFixtureList()->SetFilterData(this->engine->collisions.GetCollisionFilter("debris")->filter);

			//create joint between links
			EntityJoint *ij = link_j->Copy();

			ij->a = link;
			ij->jd_rev.bodyA = link->GetBody();
			ij->jd_rev.localAnchorA = b2Vec2(link->GetBody()->GetLocalPoint(b2Vec2(link_next->GetX()*map->p2m,link_next->GetY()*map->p2m)));

			ij->b = link_next;
			ij->jd_rev.bodyB = link_next->GetBody();
			ij->jd_rev.localAnchorB = b2Vec2(0,0);

			ij->joint = map->world->CreateJoint(&ij->jd_rev);

			if(!ij->joint)
			{
				//ERROR
				return;
			}	

			ij->joint->SetUserData(ij);

			link->AddJoint(ij);
			link_next->AddJoint(ij);
			rope_map->joints.push_back(ij);//da mogu sve odjednom stavit alive=false
		}

		//connect chain to terrain
		{
			Sprite *link = target;
			Sprite *link_next = chain[0];

			//create joint between links
			EntityJoint *ij = link_j->Copy();

			ij->a = link;
			ij->jd_rev.bodyA = link->GetBody();
			ij->jd_rev.localAnchorA = b2Vec2(link->GetBody()->GetLocalPoint(b2Vec2(ix*map->p2m,iy*map->p2m)));

			ij->b = link_next;
			ij->jd_rev.bodyB = link_next->GetBody();
			ij->jd_rev.localAnchorB = b2Vec2(0,0);

			ij->joint = map->world->CreateJoint(&ij->jd_rev);

			if(!ij->joint)
			{
				//ERROR
				return;
			}	

			ij->joint->SetUserData(ij);

			link->AddJoint(ij);
			link_next->AddJoint(ij);
			rope_map->joints.push_back(ij);//da mogu sve odjednom stavit alive=false
		}

		//connect chain to player
		{
			Sprite *link = chain[chain.size()-1];
			link->GetBody()->GetFixtureList()->SetDensity(200);// !!!
			Sprite *link_next = player;

			//create joint between links
			EntityJoint *ij = link_j->Copy();

			ij->a = link;
			ij->jd_rev.bodyA = link->GetBody();
			ij->jd_rev.localAnchorA = b2Vec2(link->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

			ij->b = link_next;
			ij->jd_rev.bodyB = link_next->GetBody();
			ij->jd_rev.localAnchorB = b2Vec2(link_next->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

			ij->joint = map->world->CreateJoint(&ij->jd_rev);

			if(!ij->joint)
			{
				//ERROR
				return;
			}	

			ij->joint->SetUserData(ij);

			link->AddJoint(ij);
			link_next->AddJoint(ij);
			rope_map->joints.push_back(ij);//da mogu sve odjednom stavit alive=false
		}

		//add rope joint between wall and player, so the chain doesn't stretch
		{
			Sprite *link = target;
			Sprite *link_next = player;

			//create joint between links
			EntityJoint *ij = new EntityJoint();

			ij->type = e_ropeJoint;
			ij->jd_rp.maxLength = (dist*1.02)*map->p2m;
			ij->jd_rp.collideConnected = true;//mora biti inace se igrac nece htjet sudarit bez obzira na collision filtere

			ij->a = link;
			ij->jd_rp.bodyA = link->GetBody();
			ij->jd_rp.localAnchorA = b2Vec2(link->GetBody()->GetLocalPoint(b2Vec2(ix*map->p2m,iy*map->p2m)));

			ij->b = link_next;
			ij->jd_rp.bodyB = link_next->GetBody();
			ij->jd_rp.localAnchorB = b2Vec2(link_next->GetBody()->GetLocalPoint(b2Vec2(rpx*map->p2m,rpy*map->p2m)));

			ij->joint = map->world->CreateJoint(&ij->jd_rp);

			if(!ij->joint)
			{
				//ERROR
				return;
			}	

			ij->joint->SetUserData(ij);

			link->AddJoint(ij);
			link_next->AddJoint(ij);
			rope_map->joints.push_back(ij);//da mogu sve odjednom stavit alive=false
		}

		//move everything to real map
		map->MoveEntitiesFrom(rope_map,true,NULL,player->getLayer());//ovako se nece sacuvat ako se mapa save-a (save_skip)

		//delete templates
		delete chain_sp;
		delete link_j;

		this->rope_map = rope_map;//save so the whole group can be deleted later
	}
}

bool Player::UpdateRope_Prismatic(bool simple, Map *map)
{
	//move up/down the rope
	if(this->rope)
	{
		b2PrismaticJoint *pj = (b2PrismaticJoint*)(this->rope->joint);

		if(this->engine->input->GetKey(SDLK_w))			pj->SetMotorSpeed(-6);
		else if(this->engine->input->GetKey(SDLK_s))	pj->SetMotorSpeed(6);
		else pj->SetMotorSpeed(0);
	}

	//remove existing rope or create new one
	if(this->engine->input->GetMsBttnR(3))
	{
		if(this->rope_map)
		{
			this->RemoveRope_Prismatic(true,true,true,true);
			return true;
		}

		b2Vec2 intersectionPoint, intersectionNormal;
		b2Body *target = this->ShootRope(intersectionPoint,intersectionNormal);
		if(target)
		{
			this->MakeRope_Prismatic(
				simple,intersectionPoint.x*map->m2p+intersectionNormal.x*5,intersectionPoint.y*map->m2p+intersectionNormal.y*5,
				(Sprite*)target->GetUserData(),this->p_player,map,true,0);

			return true;
		}		
	}

	//ninja rope
	if(this->rope_type==3 && this->rope_map)
	{
		//check if existing rope can reconnect
		if(!this->Rope_Reconnect(map))
		{
			//check if rope should split, split if break is between last point and player
			float speed = ((b2RevoluteJoint*)this->rope_revolute_i->joint)->GetJointSpeed();
			
			if(
				(speed!=0)
				&&
				(!this->rope_breakpoints.empty())
				)
			{
				this->RemoveRope_Prismatic(true,false,false,false);
				this->MakeRope_Prismatic(false,this->rope_breakpoints[0].GetX(),this->rope_breakpoints[0].GetY(),this->rope_break,this->p_player,map,true,speed);

				//save speed/direction to know when to reconnect
				this->rope_points[this->rope_points.size()-1].SetZ(speed);				
			}
		}
	}	

	return false;
}

bool Player::Rope_Reconnect(Map *map)
{	
	//return false;

	//if one direct line return
	if(this->rope_points.size()<2) return false;

	//current and saved speed/direction for vertex
	float c_speed = ((b2RevoluteJoint*)this->rope_revolute_i->joint)->GetJointSpeed();
	float s_speed = this->rope_points[this->rope_points.size()-1].GetZ();	

	bool reconnect = false;
	
	//check has player moved left/right compared to last two rope points

	float x1 = this->rope_points[this->rope_points.size()-2].GetX();
	float y1 = this->rope_points[this->rope_points.size()-2].GetY();

	float x2 = this->rope_points[this->rope_points.size()-1].GetX();
	float y2 = this->rope_points[this->rope_points.size()-1].GetY();

	float px = this->p_player->GetX() + this->rope_px;
	float py = this->p_player->GetY() + this->rope_py;

	if(c_speed<0)//clockwise
	{			
		if(s_speed>0)
		{
			//left
			if(
				((x2 - x1)*(py - y1) - (y2 - y1)*(px - x1)) > 0
				)
			{
				reconnect = true;
				this->rope_points.pop_back();
				this->rope_sprites.pop_back();
				this->rope_sprites_vertices.pop_back();
			}				
		}
	}
	else if(c_speed>0)//counter clockwise
	{
		if(s_speed<0)
		{
			//right
			if(
				((x2 - x1)*(py - y1) - (y2 - y1)*(px - x1)) < 0
				)
			{
				reconnect = true;
				this->rope_points.pop_back();
				this->rope_sprites.pop_back();
				this->rope_sprites_vertices.pop_back();
			}
		}
	}

	if(reconnect)
	{
		this->RemoveRope_Prismatic(true,false,false,false);

		this->MakeRope_Prismatic(
			false,
			this->rope_points[this->rope_points.size()-1].GetX(),
			this->rope_points[this->rope_points.size()-1].GetY(),
			this->rope_sprites[this->rope_points.size()-1],
			this->p_player,map,false,c_speed);

		return true;
	}

	return false;
}

void Player::CollisionPointToVertex(float &xx, float &yy, Sprite *a)
{
	//move the collision point a bit outwards from the terrain, so the rope tip doesn't collide

	//max distance to vertex, final offset from vertex
	float dist = 5;
	float offset = 3;

	for(unsigned int k=0;k<a->GetShpR()->tf.size();k++)
	{
		float x = a->GetShpR()->tf[k].p.GetX();
		float y = a->GetShpR()->tf[k].p.GetY();

		if(_Distance(x,y,xx,yy)<dist)
		{
			//before, after (clockwise rotation)
			float x1, y1, x2, y2;

			if(k==0)
			{
				x1 = a->GetShpR()->tf[a->GetShpR()->tf.size()-1].p.GetX();
				y1 = a->GetShpR()->tf[a->GetShpR()->tf.size()-1].p.GetY();
				x2 = a->GetShpR()->tf[k+1].p.GetX();
				y2 = a->GetShpR()->tf[k+1].p.GetY();
			}
			else if(k==a->GetShpR()->tf.size()-1)
			{
				x1 = a->GetShpR()->tf[k-1].p.GetX();
				y1 = a->GetShpR()->tf[k-1].p.GetY();
				x2 = a->GetShpR()->tf[0].p.GetX();
				y2 = a->GetShpR()->tf[0].p.GetY();
			}
			else
			{
				x1 = a->GetShpR()->tf[k-1].p.GetX();
				y1 = a->GetShpR()->tf[k-1].p.GetY();
				x2 = a->GetShpR()->tf[k+1].p.GetX();
				y2 = a->GetShpR()->tf[k+1].p.GetY();
			}

			float angle1 = _AngleToTarget(x1,y1,x,y);
			float angle2 = _AngleToTarget(x2,y2,x,y);
			float angle = _AngleToTarget(x,y,x + 10*(cos(angle1) + cos(angle2)),y + 10*(sin(angle1) + sin(angle2)));

			xx = x + offset*(cos(angle));
			yy = y + offset*(sin(angle));

			return;
		}
	}
}

//handling collision of rope with the terrain

void Player::Rope_BeginContact(b2Contact *contact, b2Fixture *fa, b2Fixture *fb)
{
	Sprite *a = (Sprite*)fa->GetBody()->GetUserData();
	Sprite *b = (Sprite*)fb->GetBody()->GetUserData();

	if(a->getText()=="rope")
	{
		if(this->rope_type==3) this->begin_fixtures.push_back(fb);//ninja rope only
		contact->SetEnabled(false);
	}
	else if(b->getText()=="rope")
	{
		if(this->rope_type==3) this->begin_fixtures.push_back(fa);//ninja rope only
		contact->SetEnabled(false);
	}
}

void Player::Rope_PreSolve(b2Contact *contact, const b2Manifold *oldManifold, b2Fixture *fa, b2Fixture *fb)
{
	//only bullet bodies get precise collision point, so rope needs to collide, but not resolve collision
	contact->SetEnabled(false);

	//return;

	if(this->rope_type!=3) return;//ninja rope only

	Sprite *a = (Sprite*)fa->GetBody()->GetUserData();
	Sprite *b = (Sprite*)fb->GetBody()->GetUserData();	

	bool skip = true;

	//add break point only if begin contact occured in the same frame (because presolve can be caled multiple times), else skip
	//this check is probably not necesarry
	if(a->getText()=="rope")
	{
		for(unsigned int i=0;i<this->begin_fixtures.size();i++)		
			if(this->begin_fixtures[i]==fb)
				skip = false;
		
	}
	else
	{
		for(unsigned int i=0;i<this->begin_fixtures.size();i++)		
			if(this->begin_fixtures[i]==fa)
				skip = false;		
	}

	if(!skip)
	{
		if((a->GetBody()->GetType()==b2_staticBody || b->GetBody()->GetType()==b2_staticBody) && contact->GetManifold()->pointCount>0)
		{
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);

			float x = worldManifold.points[0].x*map->m2p;
			float y = worldManifold.points[0].y*map->m2p;

			//check if contact point is between player and start of rope
			if(
				_Distance(this->rope_points[this->rope_points.size()-1].GetX(),this->rope_points[this->rope_points.size()-1].GetY(),x,y)
				<
				_Distance(this->rope_points[this->rope_points.size()-1].GetX(),this->rope_points[this->rope_points.size()-1].GetY(),this->p_player->GetX()+this->rope_px,this->p_player->GetY()+this->rope_py)
				)
			{
				this->rope_breakpoints.clear();
				this->rope_break = NULL;

				if(a->getText()=="rope") this->rope_break = b;
				else this->rope_break = a;

				this->CollisionPointToVertex(x,y,this->rope_break);
				this->rope_breakpoints.push_back(Vector3(x,y,0));

				////debug stuff
				MapNotification *n = new MapNotification();
				n->lifetime = 1500;
				n->type = "rope_breakpoint";

				n->x = worldManifold.points[0].x*map->m2p;
				n->y = worldManifold.points[0].y*map->m2p;
				n->numbers.push_back(worldManifold.normal.x);
				n->numbers.push_back(worldManifold.normal.y);

				n->text.push_back(_toString((int)this->engine->settings->delta_tick.frame));

				if(this->rope_revolute_i)
				{
					n->numbers.push_back(((b2RevoluteJoint*)this->rope_revolute_i->joint)->GetJointAngle());
					n->numbers.push_back(this->sprite_rope->GetBody()->GetPosition().x);
					n->numbers.push_back(this->sprite_rope->GetBody()->GetPosition().y);
					n->numbers.push_back(this->sprite_rope->GetBody()->GetAngle());
				}

				if(contact->GetManifold()->pointCount>1)
				{
					n->numbers.push_back(worldManifold.points[1].x*map->m2p);
					n->numbers.push_back(worldManifold.points[1].y*map->m2p);
				}

				map->notifications.push_back(n);
				////
			}
		}
	}
}

//removing rope objects and stuff

void Player::RemoveRope_Joint()
{
	if(this->rope)
	{
		this->rope->SetAlive(false);
		this->rope = NULL;
		if(this->rope_effect)
		{
			this->rope_effect->SetAlive(false);
			this->rope_effect = NULL;
		}

		this->rope_points.clear();
		this->rope_sprites.clear();
		this->rope_sprites_vertices.clear();
	}
}

void Player::RemoveRope_Chain()
{
	if(this->rope_map)
	{
		this->rope_map->SetAlive_Entities(false);
		delete this->rope_map;
		this->rope_map = NULL;
	}
}

void Player::RemoveRope_Prismatic(bool objects, bool rest, bool collisions, bool sprites)
{
	//rope object
	if(objects && this->rope_map)
	{
		this->rope_map->SetAlive_Entities(false);
		delete this->rope_map;
		this->rope_map = NULL;

		this->rope = NULL;
		this->rope_revolute_i = NULL;

		this->rope_length = 640;

		if(sprites)
		{
			this->sprite_rope = NULL;
			this->sprite_slider = NULL;
			this->sprite_rotor = NULL;
		}

		if(this->rope_effect)
		{
			this->rope_effect->SetAlive(false);
			this->rope_effect = NULL;
		}		
	}

	//other parts of rope
	if(rest)
	{
		this->rope_points.clear();
		this->rope_sprites.clear();
		this->rope_sprites_vertices.clear();
	}

	//current collisions for splitting rope
	if(collisions)
	{
		this->rope_breakpoints.clear();
		this->rope_break = NULL;
	}
}