#!/usr/bin/env python

import time
import psutil


class Filtervalue:
	def __init__(self, initialvalue):
		self.averagevalue = initialvalue
	
	# def __init__(self, initialvalue, sumcount):
		# self.sumcount = sumcount
		# self.lastvalues = []
		
		# for x in range(0, self.sumcount+1):		#0-100
			# self.lastvalues[x] = self.averagevalue
		
	
	def updatevalue(self, newvalue, avgweight):		# three different types of filter
		# sumofvalues = 0
		
		# self.lastvalues[self.sumcount] = self.newvalue	#100
		
		# for x in range(0, self.sumcount):		#0-99
			# self.lastvalues[x] = self.lastvalues[x+1]
			# sumofvalues += self.lastvalues[x]
		
		# self.averagevalue = sumofvalues / self.sumcount
		
		# self.lastvalues[sumcount] = ((sumofvalues * (1-avgweight)) + (self.newvalue * (avgweight))) / sumcount		#extra filtering
		
		self.averagevalue = (self.averagevalue * (1-avgweight)) + (self.newvalue * avgweight)