#pragma once
class RainComponent : public MonoBehaviour {
private:
	Transform *target;
	Vector3 color;
	double range;
	double startSpeed;
	double gravity;
	double height;
	double groundHeight;
	double lineLengthPerVelocity;
	double dropsInterval;
	double circleRadius;
	double circleDyingSpeed;
	double timer = 0;

	class RainDrop {
	public:
		double height;
		double vy;
		double x;
		double z;
		RainDrop* previous;
		RainDrop* next;

		RainDrop(double height,
			double vy,
			double x,
			double z,
			RainDrop* previous,
			RainDrop* next) :
			height(height),
			vy(vy),
			x(x),
			z(z),
			previous(previous),
			next(next) {}
	};
	class RainDropCircle {
	public:
		double x;
		double z;
		double life = 1;
		RainDropCircle* previous;
		RainDropCircle* next;

		RainDropCircle(
			double x,
			double z,
			RainDropCircle* previous,
			RainDropCircle* next) :
			x(x),
			z(z),
			previous(previous),
			next(next) {}
	};

	RainDrop * drops = NULL;
	RainDropCircle * circles = NULL;

	Vector3 getRandRange(double range) {
		double randAngle = (double)rand();
		double out = (2 * ((double)rand() / RAND_MAX) - 1);
		//out = out > 0 ? out*out : -out*out;
		out *= range;
		return  Vector3(out * sin(randAngle), 0, out*cos(randAngle));
	}

public:
	RainComponent(
		Transform *target, const Vector3 & color, double range, double startSpeed, double gravity, double height, double groundHeight, double lineLengthPerVelocity, double dropsPerSecond, double circleRadius, double circleLife)
		:target(target), color(color), range(range), startSpeed(startSpeed), gravity(gravity), height(height), groundHeight(groundHeight), lineLengthPerVelocity(lineLengthPerVelocity), dropsInterval(1.0f / dropsPerSecond), circleRadius(circleRadius), circleDyingSpeed(1.0f / circleLife) {}
	void Update() override {
		Vector3 tPos = target->GetPosition();
		timer += deltaTime;
		while (timer > dropsInterval) {
			timer -= dropsInterval;
			//drop born
			Vector3 bornPos = getRandRange(range);
			RainDrop* newDrop = new RainDrop(height, startSpeed, tPos.x + bornPos.x, tPos.z + bornPos.z, NULL, drops);
			if (drops != NULL)
				drops->previous = newDrop;
			drops = newDrop;
		}
		for (RainDrop* rp = drops; rp != NULL;)
		{
			if (rp->height <= groundHeight) {
				//circle born
				RainDropCircle* newCircle = new RainDropCircle(rp->x, rp->z, NULL, circles);
				if (circles != NULL)circles->previous = newCircle;
				circles = newCircle;
				//rp die
				if (rp->previous == NULL)drops = rp->next;
				else rp->previous->next = rp->next;
				if (rp->next != NULL)rp->next->previous = rp->previous;
				RainDrop* t = rp->next;
				delete rp;
				rp = t;
				continue;
			}
			rp->vy += gravity * deltaTime;
			rp->height -= rp->vy * deltaTime;
			rp = rp->next;
		}

		for (RainDropCircle* rc = circles; rc != NULL;) {
			if (rc->life <= 0) {
				//circle die
				if (rc->previous == NULL)circles = rc->next;
				else rc->previous->next = rc->next;
				if (rc->next != NULL)rc->next->previous = rc->previous;

				RainDropCircle *t = rc->next;
				delete rc;
				rc = t;
				continue;
			}
			rc->life -= circleDyingSpeed*deltaTime;
			rc = rc->next;
		}
	}
	void Render() override {
		Shaders::List()->unit4.use();
		glBegin(GL_LINES);
		glColor3d(color.x, color.y, color.z);
		for (RainDrop* rp = drops; rp != NULL;rp = rp->next)
		{
			glVertex3d(rp->x, rp->height, rp->z);
			glVertex3d(rp->x - CamVelocityRecorder::currentVelocity.x*lineLengthPerVelocity, rp->height - rp->vy*lineLengthPerVelocity - CamVelocityRecorder::currentVelocity.y*lineLengthPerVelocity, rp->z - CamVelocityRecorder::currentVelocity.z*lineLengthPerVelocity);
		}
		glEnd();

		for (RainDropCircle* rc = circles; rc != NULL;rc = rc->next) {
			glColor3d(color.x * rc->life, color.y * rc->life, color.z * rc->life);
			DrawCircle(rc->x, rc->z, circleRadius *(1 - rc->life));
			rc->life -= circleDyingSpeed*deltaTime;
		}
		Shader::useNone();
	}

	void DrawCircle(double x, double z, double radius) {
		glBegin(GL_LINE_LOOP);
		glVertex3d(x + radius, groundHeight, z);
		glVertex3d(x + radius * 0.707f, groundHeight, z + radius * 0.707f);
		glVertex3d(x, groundHeight, z + radius);
		glVertex3d(x - radius * 0.707f, groundHeight, z + radius * 0.707f);
		glVertex3d(x - radius, groundHeight, z);
		glVertex3d(x - radius * 0.707f, groundHeight, z - radius * 0.707f);
		glVertex3d(x, groundHeight, z - radius);
		glVertex3d(x + radius * 0.707f, groundHeight, z - radius * 0.707f);
		glEnd();
	}
};
