from arbotix_python.arbotix import ArbotiX
from servos_registers import *

ids = range(1,7) # list of servos ids
class ArbotiX_extended(ArbotiX):

	def __init__(self, port = "/dev/ttyUSB0", baud = 115200):
		
		ArbotiX.__init__(self, port, baud)
		print "Inititalizing robot connection"
		while ( self.getPosition(1) == -1 ):
			pass
		print "Done"
		self.setAllSpeeds( 50 )
	
	## @brief Read 2 bytes of registers on each servo.
	##
	## @param registerName The register to read at.(string)
	##
	## @return A list of 6 integers.
	def readAll( self , registerName ):
		reg = registersDict[registerName]
		tab = self.syncRead( ids , reg[0] , reg[1])		
		res = [0]*6 #table to write the 6 positions
		for i in ids:
			res[i-1] = tab[2*i-2] + ( tab[2*i-1]<<8 )
		
		return res
	
	## @brief Write 2 bytes to registers on each servo.
	##
	## @param registerName The register to write to. (string)
	##
	## @param values A list of 6 integers < 2^16
	def writeAll(self, registerName , values ):
		reg = registersDict[registerName]
		tab = [None] * 6
		if( reg[1] == 2 ):
			for i in ids:
				tab[i-1] = [ i , values[i-1]%256 , values[i-1]>>8 ]
		else:
			for i in ids:
				tab[i-1] = [ i , values[i-1]%256 ]
		
		self.syncWrite( reg[0] , tab )
	
	## @brief Get actual position of each servo.
	##
	## @return A list of 6 positions
	def getAllPositions( self ):
		return self.readAll( "PRESENT_POSITION" )

	
	## @brief Set goal position for each servo.
	##
	## @param values A list of 6 goal positions
	def setAllPositions( self , values ):
		self.writeAll( "GOAL_POSITION" , values )

	## @brief Set goal speed for each servo.
	##
	## @param values A list of 6 goal speeds
	## or 1 integer to set all 6 servo to the same speed
	def setAllSpeeds( self , values ):
		if ( isinstance( values , int ) ):	#if we have an integer
			values = [ values ] * 6		#we make a list containing 6 times this integer
		self.writeAll( "GOAL_SPEED" , values )

	## @brief Get goal speed of each servo.
	##
	## @return A list of 6 speeds
	def getAllSpeeds( self ):
		return self.readAll( "GOAL_SPEED" )
