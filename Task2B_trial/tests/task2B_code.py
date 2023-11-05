#python
bike = None
motor = None
base = None
Er = Ey = lastEy = Dy = Ir = Iy =  0
Kpr = 7
Kpy = -3#-3
Kdy = 12
Kir = 21
Kiy = -1.5

def sysCall_init():
    # do some initialization here
    global bike, motor, base
    bike = sim.getObjectHandle('bike_respondable')
    motor = sim.getObjectHandle('front_motor')
    base = sim.getObjectHandle('reference_frame')
    
    pass

def sysCall_actuation():
    # put your actuation code here
    global motor, Ey, Er, Kpr, Kpy, Dy, Ir, Kir, Kiy
    
    U = Kpr*Er + Kpy*Ey - Kdy*Dy + Kir*Ir + Kiy*Iy
    print('U')
    print(U)
    sim.setJointTargetVelocity(motor, U)
    pass

def sysCall_sensing():
    # put your sensing code here
    global bike , motor, base, Er, Ey, lastEy, Dy, Ir, Iy
    yaw_point = sim.getFloatSignal("yaw_setpoint")
    if yaw_point == None:
        yaw_point = 0
    else:
        yaw_point*=180/math.pi
    print('Yaw')
    print(yaw_point)
    a,b,g = sim.getObjectOrientation(bike, base)
    y,r,p = sim.alphaBetaGammaToYawPitchRoll(a,b,g)
    dt = sim.getSimulationTimeStep()
    y *=180/math.pi
    r *=180/math.pi
    p *=180/math.pi
    print([y,p,r])
    
    yaw_point = 30
    Er = r
    Ey = -yaw_point + y
    
    Dy = Ey - lastEy

    
    Ir = Ir + Er*dt
    Iy = Iy + Ey*dt
    print('Ir')
    print(Ir)
    print('Iy')
    print(Iy)
    print('Dy')
    print(Dy)
    
    
    lastEy = Ey
    
    pass

def sysCall_cleanup():
    # do some clean-up here
    pass

# See the user manual or the available code snippets for additional callback functions and details
