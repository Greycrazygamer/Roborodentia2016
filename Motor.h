class Motor
{
    private:
        byte channelA;
        byte channelB;
        byte PWM;
    public:
        Motor(byte channelA, byte channelB, byte PWM);
        
        //motor moves forward at PWM speed
        void forward(byte speed = 70);
        
        //motor moves opposite direction at PWM speed
        void backward(byte speed = 70);
        
        //stops motor
        void stop();
};

