
module robot
{
	enum eMotor { eMotorLeft, eMotorRight };
	interface motor
	{
		//Moving robot
		void move(long distance);
		void rotate(long angle);
		long measure();
	};
};