import numpy as np
import matplotlib.pyplot as plt


# Experiment will take 2 hours (120 minutes)

# Shocks are delivered every 10+-random normally distributed list

# This program generates the delay time between each 100ms shock

# Using standard_normal() method


rest=(120*60)/10

#generating the periods

resting_p=np.random.normal(loc=10000.0, scale=1000, size=750)

shocking_p=np.random.normal(loc=100.0, scale=10, size=750)

period_rest=resting_p.astype(int)

period_shock=shocking_p.astype(int)

#Test for the duration and cycles it takes for a 2 hour run


time=0
r=0
k=[]
# goes to 2 hours and 5 minutes
while time<=7500000:
    time+=period_rest[r]
    k.append(period_rest[r])
    time+=period_shock[r]
    k.append(period_shock[r])
    r+=1
    
print(time)
print(r)
print(k)








plt.hist(period_shock, bins = 50, density = True)
plt.savefig('period_shock.png')
plt.clf()
plt.hist(period_rest, bins = 50, density = True)
plt.savefig('period_rest.png')

#period_rest=period_rest.tolist()
#period_shock=period_shock.tolist()

np.savetxt('period_rest.txt', period_rest, fmt='%s,')

np.savetxt("combined_period.txt", k, fmt='%s,')

np.savetxt("period_shock.txt", period_shock,fmt='%s,')




#plt.show()
