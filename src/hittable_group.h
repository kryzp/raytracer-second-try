#ifndef HITTABLE_GROUP_H
#define HITTABLE_GROUP_H

#include "hittable.h"
#include "constants.h"

class HittableGroup : public Hittable
{
public:
	HittableGroup();
	HittableGroup(const Ref<Hittable>& obj);

	void clear();
	void add(const Ref<Hittable>& obj);

	bool hit(const Ray& r, double t_min, double t_max, Hit* hit) const override;

	Vector<Ref<Hittable>> objects;
};

#endif // HITTABLE_GROUP_H
