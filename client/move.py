import Ice
from motor_ice import motorPrx

communicator = Ice.initialize()
proxy = communicator.stringToProxy("Motors:tcp -h 192.168.0.12 -p 10001")
motor = motorPrx.checkedCast(proxy)

