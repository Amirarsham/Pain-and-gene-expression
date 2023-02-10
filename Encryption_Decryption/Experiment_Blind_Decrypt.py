import math

code=int(input("Please enter the code recorded at the begining of the experiment: "))

n=code
def primeFactors(n):
    fact=[]
    while n % 2 == 0:
        fact.append(2)
        n = n / 2
    for i in range(3,int(math.sqrt(n))+1,2):
            while n % i== 0:
                fact.append(i)
                n = n / i
    if n > 2:
        fact.append(n)
    return(fact)
   
a=[11, 13, 17, 19, "Row A"]
b=[23, 29, 31, 37, "Row B"]
c=[41, 43, 47, 53,"Row C"]
d=[59, 61, 67, 71,"Row D"]

randomiser=[103, 107, 109, 113, 127, 131, 137, 139, 149, 151]

factored=primeFactors(code)
factored.sort()
output=''

for i in range(len(factored)):
    if factored[i] in a:
        output+=a[4]+" And "
    if factored[i] in b:
        output+=b[4]+" And "
    if factored[i] in c:
        output+=c[4]+" Were The Rows With Noxious Stimuli. All The Best"
    if factored[i] in d:
        output+=d[4]+" Were The Rows With Noxious Stimuli. All The Best"


           
print(output)
        
