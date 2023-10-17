1;

pkg load control;
pkg load symbolic;

##**************************************************************************
##*                OCTAVE PROGRAMMING (e-Yantra)
##*                ====================================
##*  This software is intended to teach Octave Programming and Mathematical
##*  Modeling concepts
##*  Theme: Lunar Scout
##*  Filename: Task_1A.m
##*  Version: 1.0.0  
##*  Date: 18/09/2023
##*
##*  Team ID :
##*  Team Leader Name:
##*  Team Member Name
##*
##*  
##*  Author: e-Yantra Project, Department of Computer Science
##*  and Engineering, Indian Institute of Technology Bombay.
##*  
##*  Software released under Creative Commons CC BY-NC-SA
##*
##*  For legal information refer to:
##*        http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 
##*     
##*
##*  This software is made available on an �AS IS WHERE IS BASIS�. 
##*  Licensee/end user indemnifies and will keep e-Yantra indemnified from
##*  any and all claim(s) that emanate from the use of the Software or 
##*  breach of the terms of this agreement.
##*  
##*  e-Yantra - An MHRD project under National Mission on Education using 
##*  ICT(NMEICT)
##*
##**************************************************************************

## Function : Jacobian_A_B()
## ----------------------------------------------------
## Input:   Mp                - mass of the pendulum
##          l                 - Length of Pendulum
##          g                 - Acceleration due to gravity
##          Ma                - mass of the arm
##          Rp                - length of pendulum base from the pivot point
##          Ra                 - length from arm's center of mass to arm's pivot point
##          I_arm             - Moment of inertia of the arm in yaw angle
##          I_pendulum_theta  - Moment of inertia of the pendulum in tilt angle
##          I_pendulum_alpha  - Moment of inertia of the pendulum in yaw angle
##
## Output:  A - A matrix of system (State or System Matrix )
##          B - B matrix of system (Input Matrix)
##          
## Purpose: Use jacobian function to find A and B matrices(State Space Model) in this function.

function [A,B] = Jacobian_A_B(Mp,l,g,Ma,Rp,Ra,I_arm,I_pendulum_theta,I_pendulum_alpha)

  alpha = sym('alpha');
  theta = sym('theta');
  theta_dot = sym('theta_dot');
  alpha_dot = sym('alpha_dot');
  u = sym('u');
  
  cos_theta = cos(theta);
  sin_theta = sin(theta);

  cos_alpha = cos(alpha);
  sin_alpha = sin(alpha);
  
  ########## ADD YOUR CODE HERE ################
  #{
  Steps : 
    1. Define equations of motion (4-states so 4 equations). It is suggested to use Lagrangian method. You can try Newtonian methods too.
    2. Partial Differentiation of equations of motion to find the Jacobian matrices
    3. Linearization by substituting equillibrium point condition in Jacobians
  
  ### NOTE ### : Sequence of states should not be altered for evaluation
  
  SEQUENCE OF STATES : [alpha_dot; alpha; theta_dot; theta]
        Example:
                A = [x x x x;   # corresponds to ...alpha_dot
                     x x x x;   # ...alpha
                     x x x x;   # ...theta_dot
                     x x x x]   # ...theta
                B = [x;   # ...alpha_dot
                     x;   # ...alpha
                     x;   # ...theta_dot
                     x]   # ...theta  
  #}
  ##############################################  
  x1 = alpha
  x2 = alpha_dot
  x3 = theta
  x4 = theta_dot
  m2 = Mp;
  I1 = I_arm;
  I2 = I_pendulum_theta;
  r = Rp;
  
  
##  x1_dot = x2
##  x2_dot = -(l*Mp*sin_theta *(I_pendulum_theta *Rp*x4 + l^2*Mp*Rp*x4 - l^2*Mp*Rp*x2^2*cos_theta ^2 + 2*l^3*Mp*x2*x4*cos_theta  + 2*I_pendulum_theta *l*x2*x4*cos_theta  - g*l*Mp*Rp*cos_theta ))/(I_arm*I_pendulum_theta  + l^4*Mp^2 - l^4*Mp^2*cos_theta ^2 + l^2*Mp^2*Rp^2 + I_arm*l^2*Mp + I_pendulum_theta *l^2*Mp + I_pendulum_theta *Mp*Rp^2 - l^2*Mp^2*Rp^2*cos_theta ^2 - I_pendulum_theta *l^2*Mp*cos_theta ^2);
##  x3_dot = x4
##  x4_dot = (l*Mp*(8*I_arm*g*sin_theta  + 4*I_arm*l*x2^2*sin(2*x3) - 2*g*l^2*Mp*sin(3*x3) + 2*l^3*Mp*x2^2*sin(2*x3) - l^3*Mp*x2^2*sin(4*x3) + 6*g*l^2*Mp*sin_theta  + 8*g*Mp*Rp^2*sin_theta  + 4*l*Mp*Rp^2*x2^2*sin(2*x3) - 4*l*Mp*Rp^2*x4*sin(2*x3) - 4*l^2*Mp*Rp*x2*x4*sin(3*x3) - 4*l^2*Mp*Rp*x2*x4*sin_theta ))/(8*(I_arm*I_pendulum_theta  + l^4*Mp^2 - l^4*Mp^2*cos_theta ^2 + l^2*Mp^2*Rp^2 + I_arm*l^2*Mp + I_pendulum_theta *l^2*Mp + I_pendulum_theta *Mp*Rp^2 - l^2*Mp^2*Rp^2*cos_theta ^2 - I_pendulum_theta *l^2*Mp*cos_theta ^2));


##  x1_dot = x2
##  x2_dot =-(l*m2*sin(x3)*(l^2*m2*r*x2^2*cos(x3)^2 - l^2*m2*r*x4^2 - I2*r*x4^2 + 2*l^3*m2*x2*x4*cos(x3) + 2*I2*l*x2*x4*cos(x3) + g*l*m2*r*cos(x3)))/(I1*I2 + l^4*m2^2 - l^4*m2^2*cos(x3)^2 + l^2*m2^2*r^2 + I1*l^2*m2 + I2*l^2*m2 + I2*m2*r^2 - l^2*m2^2*r^2*cos(x3)^2 - I2*l^2*m2*cos(x3)^2)
##  x3_dot = x4
##  x4_dot = (g*l*m2*sin(x3) + l^2*m2*x2^2*cos(x3)*sin(x3) - (l^2*m2^2*r*x4*cos(x3)*(r*x4*sin(x3) - 2*l*x2*cos(x3)*sin(x3)))/(m2*l^2*sin(x3)^2 + m2*r^2 + I1))/(I2 + l^2*m2 + (l^2*m2^2*r^2*(sin(x3)^2 - 1))/(m2*l^2*sin(x3)^2 + m2*r^2 + I1))
  
  
  x1_dot = x2
  x2_dot = (I2*u + l^2*m2*u + l^3*m2^2*r*x4^2*sin(x3) - l^3*m2^2*r*x2^2*cos(x3)^2*sin(x3) - g*l^2*m2^2*r*cos(x3)*sin(x3) - 2*l^4*m2^2*x2*x4*cos(x3)*sin(x3) + I2*l*m2*r*x4^2*sin(x3) - 2*I2*l^2*m2*x2*x4*cos(x3)*sin(x3))/(I1*I2 + l^4*m2^2 - l^4*m2^2*cos(x3)^2 + l^2*m2^2*r^2 + I1*l^2*m2 + I2*l^2*m2 + I2*m2*r^2 - l^2*m2^2*r^2*cos(x3)^2 - I2*l^2*m2*cos(x3)^2)
  x3_dot = x4
  x4_dot = (g*l*m2*sin(x3) + l^2*m2*x2^2*cos(x3)*sin(x3) - (l*m2*r*cos(x3)*(- 2*m2*x2*cos(x3)*sin(x3)*l^2*x4 + m2*r*sin(x3)*l*x4^2 + u))/(m2*l^2*sin(x3)^2 + m2*r^2 + I1))/(I2 + l^2*m2 - (l^2*m2^2*r^2*cos(x3)^2)/(m2*l^2*sin(x3)^2 + m2*r^2 + I1))
  
##  
##  x1_dot = x2
##  x2_dot = -(Rw^2*(l^4*x2*x4*sin(2*x3) - 20*l^2*u - 400*l^2*m2*u - l^3*r*x4^2*sin(x3) - 400*I2*u + l^3*r*x2^2*(sin(x3) - sin(x3)^3) + 200*g*l^2*m2^2*r*sin(2*x3) - 400*l^3*m2^2*r*x4^2*sin(x3) + 400*l^4*m2^2*x2*x4*sin(2*x3) + 400*l^3*m2^2*r*x2^2*(sin(x3) - sin(x3)^3) - 20*I2*l*r*x4^2*sin(x3) + 20*I2*l^2*x2*x4*sin(2*x3) + 10*g*l^2*m2*r*sin(2*x3) - 40*l^3*m2*r*x4^2*sin(x3) + 40*l^4*m2*x2*x4*sin(2*x3) + 40*l^3*m2*r*x2^2*(sin(x3) - sin(x3)^3) + 400*I2*l^2*m2*x2*x4*sin(2*x3) - 400*I2*l*m2*r*x4^2*sin(x3)))/(20*Iw*l^4 + Rw^2*l^4 - Rw^2*l^4*cos(x3)^2 + 20*I1*Rw^2*l^2 + 20*I2*Rw^2*l^2 + 20*I2*Rw^2*r^2 + 40*Rw^2*l^4*m2 + 400*I1*I2*Rw^2 + 400*Rw^2*l^4*m2^2 + Rw^2*l^2*r^2 + 400*I2*Iw*l^2 + 400*Iw*l^4*m2 + 40*Rw^2*l^2*m2*r^2 - 20*I2*Rw^2*l^2*cos(x3)^2 + 400*Rw^2*l^2*m2^2*r^2 - 40*Rw^2*l^4*m2*cos(x3)^2 + 400*I1*Rw^2*l^2*m2 + 400*I2*Rw^2*l^2*m2 + 400*I2*Rw^2*m2*r^2 - 400*Rw^2*l^4*m2^2*cos(x3)^2 - Rw^2*l^2*r^2*cos(x3)^2 - 40*Rw^2*l^2*m2*r^2*cos(x3)^2 - 400*Rw^2*l^2*m2^2*r^2*cos(x3)^2 - 400*I2*Rw^2*l^2*m2*cos(x3)^2)
##  x3_dot = x4
##  x4_dot = (g*l*m2*sin(x3) + l^2*x2^2*cos(x3)*sin(x3)*(m2 + 1/20) - (l*r*cos(x3)*(m2 + 1/20)*(u + (l*r*x4^2*sin(x3))/20 + l*m2*r*x4^2*sin(x3) - (l^2*x2*x4*cos(x3)*sin(x3))/10 - 2*l^2*m2*x2*x4*cos(x3)*sin(x3)))/(I1 + (l^2*sin(x3)^2)/20 + m2*r^2 + r^2/20 + (Iw*l^2)/Rw^2 + l^2*m2*sin(x3)^2))/(I2 + l^2*(m2 + 1/20) - (l*r*cos(x3)*(m2 + 1/20)*((l*r*cos(x3))/20 + l*m2*r*cos(x3)))/(I1 + (l^2*sin(x3)^2)/20 + m2*r^2 + r^2/20 + (Iw*l^2)/Rw^2 + l^2*m2*sin(x3)^2))
##
##  
  x1_dot==0;
  x2_dot==0;
  x3_dot==0;
  x4_dot==0;
  
  x2_dot_ = subs(x2_dot, u,0);
  x4_dot_ = subs(x4_dot, u, 0);
  eqns=[x1_dot x2_dot_ x3_dot x4_dot_];
  var=[x1 x2 x3 x4]
##  double(subs(eqns,[x1,x2,x3,x4], [0,0,0,0]))
  [x_1 x_2 x_3 x_4]=solve(eqns,var)
  eqns=[x1_dot x2_dot x3_dot x4_dot];
##  x_3 = subs(x_3, u, 0)
  jA = jacobian(eqns, var);
  jB = jacobian(eqns, u)
  

  
##  A = double(subs(jA, [x1,x2,x3,x4, u], [x_1(1), x_2(1), x_3(1), x_4(1),0]))
##  eig(A);
  A = double(subs(jA, [x1,x2,x3,x4,u], [x_1(2), x_2(2), x_3(2), x_4(2),0])) # A should be (double) datatype 
  eig(A)
  B = double(subs(jB, [x1,x2,x3,x4], [x_1(1), x_2(1), x_3(1), x_4(1)])) # B should be (double) datatype
  
endfunction

## Function : lqr_Rotary_Inverted_Pendulum()
## ----------------------------------------------------
## Input:   A - A matrix of system (State or System Matrix )
##          B - B matrix of system (Input Matrix)
##
## Output:  K - LQR Gain Matrix
##          
## Purpose: This function is used for finding optimal gains for the system using
##          the Linear Quadratic Regulator technique           

function K = lqr_Rotary_Inverted_Pendulum(A,B)
  C    =  [1 0 0 0;
          0 1 0 0;
          0 0 1 0;
          0 0 0 1];           ## Initialise C matrix
  D     = [0;0;0;0];          ## Initialise D matrix
  Q     = eye(4);             ## Initialise Q matrix
  R     = 1;                  ## Initialise R 
  sys   = ss(A,B,C,D);        ## State Space Model
  K     = lqr(sys,Q,R);       ## Calculate K matrix from A,B,Q,R matrices using lqr()
  
endfunction

## Function : Rotary_Inverted_Pendulum_main()
## ----------------------------------------------------
## Purpose: Used for testing out the various controllers by calling their 
##          respective functions.
##          (1) Tilt angle is represented as theta
##          (2) Yaw angle is represented as alpha
        
function Rotary_Inverted_Pendulum_main()
  
  Mp = 0.5 ;                  # mass of the pendulum (Kg)
  l = 0.15 ;                  # length from pendulum's center of mass to pendulum's base/pivot (meter)
  g = 9.81 ;                  # Accelertion due to gravity (kgm/s^2)
  Ma = 0.25 ;                 # mass of the arm (kg)

  r_a = 0.01;                 # radius of arm cylinder (meter)
  r_p = 0.01;                 # radius of pendulum cylinder (meter)
 
  Rp = 0.2 ;                  # length from pendulum's base to arm's pivot point (meter)
  Ra = 0.1 ;                   # length from arm's center of mass to arm's pivot point (meter)
  
  I_arm = (Ma*Rp^2)/3;                   # Moment of inertia of the arm in yaw angle i.e. alpha (kgm^2)
  I_pendulum_theta = 0.026#(Mp*(2*l)^2)/3;        # Moment of inertia of the pendulum in tilt angle i.e. theta (kgm^2)
  I_pendulum_alpha = 0;        # Moment of inertia of the pendulum in yaw angle (kgm^2)
  
  [A,B] = Jacobian_A_B(Mp,l,g,Ma,Rp,Ra,I_arm,I_pendulum_theta,I_pendulum_alpha) ## find A , B matrix using  Jacobian_A_B() function
  K = lqr_Rotary_Inverted_Pendulum(A,B)  ## find the gains using lqr_Rotary_Inverted_Pendulum() function
  
endfunction
Rotary_Inverted_Pendulum_main()