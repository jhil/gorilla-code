
#include <Servo.h> 

/*Global Variables*/
Servo servos[8];  //Servos (See below for pin assignments)
int zero[] = { 78+5, 120,
               52-5, 0,
               61-2, 120,
               85+2, 0};  //Zero or Initial angles
int lift_angle = 15;  //Lift angle for all legs
int lift_angle_up = lift_angle * 2;  //Lift angle for all legs
int lift_angle_land = lift_angle;  //Lift angle for all legs
int lift_angle_up_back = lift_angle * 2;  //Lift angle for all legs
int bend_angle = 65;  //Sweep angle for left sweep servos
int bend_angle_back = 120;  //Sweep angle for left sweep servos

int step_delay = 200;    // delay interval in sec for each step

int lift_delay = 50;     // in milli sec
int sweep_delay = 150;   // in milli sec

// NOTE: Servos provided to you have range of 120 degress.
// So, if you have zero angles to be 60 deg, then...
// it can only go between 0 deg to 120 deg.
// Thus adjust your lift and sweep angle accordingly.
 
// The setup function is used to initialize servos
void setup() 
{ 
  /*Servo Pin Setup:*/
  servos[ 0 ].attach( 2 );   // Front-Left Lift servo
  servos[ 1 ].attach( 3 );   // Front-Left end servo
  servos[ 2 ].attach( 4 );   // Front-Right lift servo
  servos[ 3 ].attach( 5 );   // Front-Right bend servo
  servos[ 4 ].attach( 6 );   // Back-Right Lift servo
  servos[ 5 ].attach( 7 );   // Back-Right bend servo
  servos[ 6 ].attach( 8 );   // Back-Left lift servo
  servos[ 7 ].attach( 9 );   // Back-Left bend servo
  
  /* write_angle is a function defined below.
     This will just send the appropriate argument
     values to the servos. */
     
  write_angles( zero[ 0 ], zero[ 1 ],
                zero[ 2 ], zero[ 3 ],
                zero[ 4 ], zero[ 5 ],
                zero[ 6 ], zero[ 7 ]);
  delay( 1000 );
  
  write_angles( lift_angle + zero[ 0 ], zero[ 1 ],
                lift_angle + zero[ 2 ],  zero[ 3 ],
                -lift_angle + zero[ 4 ],  zero[ 5 ],
                -lift_angle + zero[ 6 ],  zero[ 7 ]);
  delay( 500 );
  
}

/* This fucntion will run infinitely until we manually turn the arduino off
   It resembles to "main" function in other programming languages. */

void loop()
{

  // half cycle 1
  
  write_angles( lift_angle + zero[ 0 ], zero[ 1 ],        // Front-Left lift backwards, Front-Left bend zero
                lift_angle + zero[ 2 ],  zero[ 3 ],       // Front-Right lift forwards, Front-Right bend
                zero[ 4 ],  zero[ 5 ],                    // Back-Right lift backwards, Back-Right bend
                zero[ 6 ],  zero[ 7 ]);                   // Back-Left lift forwards, Back-Left bend
  delay( step_delay );

  write_angles( lift_angle_up + zero[ 0 ], -bend_angle + zero[ 1 ],    // Front-Left lift backwards, Front-Left bend zero
                zero[ 2 ],  zero[ 3 ],                    // Front-Right lift forwards, Front-Right bend
                zero[ 4 ],  zero[ 5 ],                    // Back-Right lift backwards, Back-Right bend
                zero[ 6 ],  zero[ 7 ]);                   // Back-Left lift forwards, Back-Left bend
  delay( step_delay );
  
  write_angles( -lift_angle_land + zero[ 0 ], -bend_angle + zero[ 1 ],    // Front-Left lift backwards, Front-Left bend zero
                -lift_angle + zero[ 2 ],  zero[ 3 ],      // Front-Right lift forwards, Front-Right bend
                lift_angle_up_back + zero[ 4 ],  -bend_angle_back + zero[ 5 ],    // Back-Right lift backwards, Back-Right bend
                zero[ 6 ],  zero[ 7 ]);                   // Back-Left lift forwards, Back-Left bend
  delay( step_delay );
  
  // half cycle 2

  write_angles( -lift_angle + zero[ 0 ], zero[ 1 ],        // Front-Left lift backwards, Front-Left bend zero
                -lift_angle + zero[ 2 ],  zero[ 3 ],       // Front-Right lift forwards, Front-Right bend
                zero[ 4 ],  zero[ 5 ],                     // Back-Right lift backwards, Back-Right bend
                zero[ 6 ],  zero[ 7 ]);                    // Back-Left lift forwards, Back-Left bend
  delay( step_delay );

  write_angles( zero[ 0 ], zero[ 1 ],                      // Front-Left lift backwards, Front-Left bend zero
                -lift_angle_up + zero[ 2 ],  bend_angle + zero[ 3 ],    // Front-Right lift forwards, Front-Right bend
                zero[ 4 ],  zero[ 5 ],                     // Back-Right lift backwards, Back-Right bend
                zero[ 6 ],  zero[ 7 ]);                    // Back-Left lift forwards, Back-Left bend
  delay( step_delay );

  write_angles( lift_angle + zero[ 0 ], zero[ 1 ],         // Front-Left lift backwards, Front-Left bend zero
                lift_angle_land + zero[ 2 ],  bend_angle + zero[ 3 ],    // Front-Right lift forwards, Front-Right bend
                zero[ 4 ],  zero[ 5 ],                     // Back-Right lift backwards, Back-Right bend
                -lift_angle_up_back + zero[ 6 ],  bend_angle_back + zero[ 7 ]);    // Back-Left lift forwards, Back-Left bend
  delay( step_delay );

}

/*Writes the argument angles to the appropriate servos*/

void write_angles( double front_left_lift,   double front_left_sweep,
                   double front_right_sweep, double front_right_lift,
                   double back_right_lift,   double back_right_sweep,
                   double back_left_sweep,   double back_left_lift)

{
  servos[ 0 ].write( front_left_lift );
  servos[ 1 ].write( front_left_sweep );
  servos[ 2 ].write( front_right_sweep );
  servos[ 3 ].write( front_right_lift );
  servos[ 4 ].write( back_right_lift );
  servos[ 5 ].write( back_right_sweep );
  servos[ 6 ].write( back_left_sweep );
  servos[ 7 ].write( back_left_lift );
}
