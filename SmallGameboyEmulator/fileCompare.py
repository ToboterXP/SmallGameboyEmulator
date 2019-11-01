
FILE_A = "log.txt"
FILE_B = "zboy-log.txt"

lineNum = 1
with open(FILE_A,"r") as fa:
    with open(FILE_B,"r") as fb:
        prev = ""
        while True:
            trueLineA = fa.readline()
            lineA = trueLineA[:-9]+"\n"
            lineB = fb.readline()

            if not (lineA and lineB):
                break

            if lineA!=lineB:
                print("Line %i:" % (lineNum))
                print("Prev:",prev)
                print("A:",trueLineA)
                print("B:",lineB)
                break

            lineNum+=1
            prev = trueLineA
        
