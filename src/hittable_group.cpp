#include "hittable_group.h"

HittableGroup::HittableGroup()
	: objects()
{
}

HittableGroup::HittableGroup(const Ref<Hittable>& obj)
	: objects()
{
	add(obj);
}

void HittableGroup::clear()
{
	objects.clear();
}

void HittableGroup::add(const Ref<Hittable>& obj)
{
	objects.push_back(obj);
}

bool HittableGroup::hit(const Ray& r, double t_min, double t_max, Hit* hit) const
{
	bool any = false;
	Hit closestHit;
	double closest = t_max;

	for (const auto& o : objects) {
		if (o->hit(r, t_min, closest, &closestHit)) {
			any = true;
			closest = closestHit.t;
			(*hit) = closestHit;
		}
	}

	return any;
}
