#python
import math
def sysCall_init():
    # do some initialization here
    print('Front motor started')
    sim.setJointTargetForce(sim.getObjectHandle('front_motor'), 50)
    pass

def sysCall_actuation():
    # put your actuation code here
    print('Vel')
    sim.setJointTargetVelocity(sim.getObjectHandle('front_motor'), 10)
    

    pass

def sysCall_sensing():
    # put your sensing code here
    _,a,t = sim.getObjectOrientation(sim.getObjectHandle('bike_respondable'), sim.getObjectHandle('reference_frame') )  #sim.getObjectHandle('reference_frame')
    #o_edit = [math.atan(math.tan(angle)) for angle in o]
    # t = (t -3.14)
    # if t < -3.14:
    #     t = t + 2*math.pi 

    
    # if not(-math.pi/2 < t and t < math.pi/2):
    #     print('t')
    #     if a > 0:
    #         a = math.pi - a
    #     else:
    #         a = -math.pi - a

    # if t > math.pi/2 :
    #     t = t-math.pi
    # elif t < -math.pi/2:
    #    t = t + math.pi  
 
    y,p,r = sim.alphaBetaGammaToYawPitchRoll(_,a,t)
    #print([180*_/math.pi,180*a/math.pi,180*t/math.pi])
    print([180*y/math.pi,180*p/math.pi,180*r/math.pi])
    pass

def sysCall_cleanup():
    # do some clean-up here
    pass

# See the user manual or the available code snippets for additional callback functions and details
