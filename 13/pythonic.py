print ''.join([c for c in str(sum([long(line) for line in open("data.txt","r")]))])[0:10]
