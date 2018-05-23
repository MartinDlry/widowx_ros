from arbotix_python.arbotix import ArbotiX
from arbotix_python.ax12 import *

ids = range(1,7) # list of servos ids
class ArbotiX_extended(ArbotiX):
	
	## @brief Read 2 bytes of registers on each servo.
	##
	## @param start The starting register address to begin reading at.
	##
	## @return A list of 6 integers.
	def readAll( self , start ):
		tab = self.syncRead( ids , start , 2)		
		res = [0]*6 #table to write the 6 positions
		for i in ids:
			res[i-1] = tab[2*i-2] + ( tab[2*i-1]<<8 )
		
		return res
	
	## @brief Write 2 bytes to registers on each servo.
	##
	## @param start The starting register address to begin writing to.
	##
	## @param values A list of 6 integers < 2^16
	def writeAll(self, start , values ):
		tab = [None] * 6
		for i in ids:
			tab[i-1] = [ i , values[i-1]%256 , values[i-1]>>8 ]
		print tab
		self.syncWrite( start , tab )
	
	## @brief Get actual position of each servo.
	##
	## @return A list of 6 positions
	def getAllPositions( self ):
		return self.readAll( P_PRESENT_POSITION_L )

	
	## @brief Set goal position for each servo.
	##
	## @param values A list of 6 goal positions
	def setAllPositions( self , values ):
		self.writeAll( P_GOAL_POSITION_L , values )

	## @brief Set goal speed for each servo.
	##
	## @param values A list of 6 goal speeds
	## or 1 integer to set all 6 servo to the same speed
	def setAllSpeeds( self , values ):
		if ( isinstance( values , int ) ):	#if we have an integer
			values = [ values ] * 6		#we make a list containing 6 times this integer
		self.writeAll( P_GOAL_SPEED_L , values )

	## @brief Get goal speed of each servo.
	##
	## @return A list of 6 speeds
	def getAllSpeeds( self ):
		return self.readAll( P_GOAL_SPEED_L )
