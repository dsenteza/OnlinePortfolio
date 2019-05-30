import re 

import sys

#https://stackoverflow.com/questions/82831/how-to-check-whether-a-file-exists?rq=1
#to check if file path exists
import os.path

baseballFile = sys.argv[1]
regex = "((?P<player>^[a-zA-Z]\s[a-zA-z])\sbatted\s(\d?P<batted>\d)\stimes\swith\s(\d?P<hits>\d)\shits\sand\s(\d?P<runs>\d)\sruns)"

#https://stackoverflow.com/questions/82831/how-to-check-whether-a-file-exists?rq=1
#line to check if file exists
if os.path.exists(baseballFile):
	file = open(baseballFile, "r")
	data = {}
	values = re.compile(regex)

	for line in file:
		#referenced https://github.com/cmoraes1/baseball-stats-counter/blob/master/stats_counter.py
		#for grabbing name, batted, and hits
		details = re.match(values, line)
		playerName = details.group('player')
		playerHits = int(details.group('batted'))
		playerBatts = int(details.group('hits'))

		if not player in data:
			data.append(playerName)
			data[name]['batted'] = playerBatts
			data[name]['hits'] = playerHits

		else:
			data[name]['batted'] = data[name]['batted'] + playerBatts
			data[name]['hits'] = data[name]['hits'] + playerHits

	stats = []
	#adding batting average to new array
	for player in stats:
		battAvg = (description[player]['playerHits'])/(description[player]['playerBatts'])
		stats.append(player, battAvg)

	#.sort() sorts the list and reverse=True makes it greatest to least
	sortedStats = stats.sort(reverse=True)
	for player in sortedStats:
		#prints out each player and their batting average
		#for rounding the stats: https://stackoverflow.com/questions/9232256/round-up-to-third-decimal-place-in-python
		print(player[0] + ":" round(player[1], 3)

#if there is no file to open
else
	print "file does not exist"