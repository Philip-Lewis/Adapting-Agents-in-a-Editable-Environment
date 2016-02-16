#include "Classes\catch.hpp"
#include "Classes\SimManager\SimManager.h"

TEST_CASE("Spawn adds desired actors to actors vector", "[spawning]")
{
	World* world = new World();
	Resource* r = new Resource(0, 0, 1, 1, 1, FOOD);
	Resource* w = new Resource(0, 0, 1, 1, 1, WATER);
	Obstacle* o = new Obstacle(0, 0);
	Agent* a = new Agent(0, 0, world, 0, 0);

	REQUIRE(((world->Spawn(nullptr) == false) && (world->getAllActors().empty())));
	REQUIRE((world->Spawn(r) && (world->getAllActors().at(0) == r)));
	REQUIRE((world->Spawn(w) && (world->getAllActors().at(1) == w)));
	REQUIRE((world->Spawn(o) && (world->getAllActors().at(2) == o)));
	REQUIRE((world->Spawn(a) && (world->getAllActors().at(3) == a)));
}

TEST_CASE("kill removes desired actor from actors vector", "[killing]")
{
	World* world = new World();
	Resource* r = new Resource(0, 0, 1, 1, 1, FOOD);
	world->Spawn(r);

	REQUIRE(((world->KillActor(r)) && (world->getAllActors().empty())));

	Resource* w = new Resource(0, 0, 1, 1, 1, WATER);
	Obstacle* o = new Obstacle(0, 0);
	Agent* a = new Agent(0, 0, world, 0, 0);
	world->Spawn(w);
	world->Spawn(o);
	world->Spawn(a);

	REQUIRE(((world->KillActor(o)) && (world->getAllActors().size() == 2)));
}

TEST_CASE("Sensor detect only return normalised vectors", "[Detecting]")
{
	World* world = new World();
	Resource* r = new Resource(0, 0, 1, 1, 1, FOOD);
	Resource* w = new Resource(1, 1, 1, 1, 1, WATER);
	Obstacle* o = new Obstacle(2, 2);
	Agent* a = new Agent(1.5, 1.5, world, 0, 0);
	Sensor* sf = new Sensor(FOOD, 5);
	Sensor* sw = new Sensor(WATER, 5);
	Sensor* so = new Sensor(OBSTACLE, 5);
	Sensor* sa = new Sensor(AGENT, 5);
	Sensor* none = new Sensor(NONE, 5);
	Vector2D res = sf->Detect(world, a);

	REQUIRE(((res.x <= 1) && (res.x >= 0)));
	REQUIRE(((res.y <= 1) && (res.y >= 0)));

	res = sw->Detect(world, a);

	REQUIRE(((res.x <= 1) && (res.x >= 0)));
	REQUIRE(((res.y <= 1) && (res.y >= 0)));

	res = so->Detect(world, a);

	REQUIRE(((res.x <= 1) && (res.x >= 0)));
	REQUIRE(((res.y <= 1) && (res.y >= 0)));

	res = sa->Detect(world, a);

	REQUIRE(res.x == 0);
	REQUIRE(res.y == 0);

	res = sa->Detect(world, a);

	REQUIRE(res.x == 0);
	REQUIRE(res.y == 0);
}

TEST_CASE("Wander adjusts the wanderTarget in either axis by value between -5 & 5", "[wandering]")
{
	World* world = new World();
	Agent* agent = new Agent(10, 10, world, 5, 5);
	Vector2D wanderTarget = agent->getWanderTarget();
	Vector2D diff = Vector2D();

	agent->update(0.5);

	diff.x = (wanderTarget.x - agent->getWanderTarget().x);
	diff.y = (wanderTarget.y - agent->getWanderTarget().y);
	REQUIRE(((diff.x >= -5) && (diff.x <= 5)));
	REQUIRE(((diff.y >= -5) && (diff.x <= 5)));

	wanderTarget = agent->getWanderTarget();

	agent->update(0.5);

	diff.x = (wanderTarget.x - agent->getWanderTarget().x);
	diff.y = (wanderTarget.y - agent->getWanderTarget().y);
	REQUIRE(((diff.x >= -5) && (diff.x <= 5)));
	REQUIRE(((diff.y >= -5) && (diff.x <= 5)));
}

TEST_CASE("Hunger can be set but is only ever between 0 and 1", "[Hunger]")
{
	World* world = new World();
	Agent*  agent = new Agent(0, 0, world, 0, 0);

	agent->setHunger(0);
	REQUIRE(agent->getHunger() == 0);
	agent->setHunger(1);
	REQUIRE(agent->getHunger() == 1);
	agent->setHunger(5);
	REQUIRE(agent->getHunger() == 1);
	agent->setHunger(-5);
	REQUIRE(agent->getHunger() == 0);
}

TEST_CASE("Thirst can be set but is only ever between 0 and 1", "[Thirst]")
{
	World* world = new World();
	Agent*  agent = new Agent(0, 0, world, 0, 0);

	agent->setThirst(0);
	REQUIRE(agent->getThirst() == 0);
	agent->setThirst(1);
	REQUIRE(agent->getThirst() == 1);
	agent->setThirst(5);
	REQUIRE(agent->getThirst() == 1);
	agent->setThirst(-5);
	REQUIRE(agent->getThirst() == 0);
}

TEST_CASE("Resources can be consumed unless quantity is equal 0", "[Consume]")
{
	Resource* r = new Resource(0, 0, 100, 100, 50, FOOD);

	REQUIRE(r->consume(50) == 0.5);
	REQUIRE(r->consume(50) == 0.5);
	REQUIRE(r->consume(50) == 0);

	r->regenerateQuantity(100);

	REQUIRE(r->consume(150) == 1);
}