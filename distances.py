import codecs
import numpy as np

def loadDatabase(path=''):
    """"loads the music dataset"""
    
    data={}

    f=codecs.open(path+"Music.csv",'r','utf8')

    lineset = [line for line in f]

    users = lineset[0].split(',')

    for i in range(1,len(lineset)):
        fields = lineset[i].split(',')
        book = fields[0].strip('"')

        currentRatingB={}
        for j in range(1,len(fields)):
            if users[j].strip('"') in data:
                currentRating=data[users[j].strip('"')]
            else:
                currentRating={}
            if fields[j].strip().strip('"'):
                currentRating[book]=float(fields[j].strip().strip('"'))
                data[users[j].strip('"')] = currentRating
                currentRatingB[users[j].strip('"')]=float(fields[j].strip().strip('"'))
        data[book] = currentRatingB

    f.close()
    return data

def distanceManhattan(u_rating1,u_rating2):

    distance = 0

    for key in u_rating1:
        if key in u_rating2:
            distance += abs(u_rating1[key] - u_rating2[key])
    return distance


def distanceEuclides(u_rating1,u_rating2):

    distance = 0
    for key in u_rating1:
        if key in u_rating2:
            distance += pow(u_rating1[key] - u_rating2[key],2)
    return np.sqrt(distance)

data=loadDatabase()

#print(data)
#print(distanceEuclides(data['Hailey'],data['Jordyn']))
print(distanceManhattan(data['Blues Traveler'],data['Deadmau5']))
#print(distanceEuclides(data['Bryan'],data['Heather']))
