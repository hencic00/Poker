import os
import sys
import re

dir = sys.argv[1]
r = []
subdirs = [x[0] for x in os.walk(dir)]
asd = subdirs[0]
m = re.search('(\d+)', subdirs[0])
porociloNr = m.group(0)
print("Generating Porocilo {}\n".format(porociloNr))
porociloDir = "Nal"+porociloNr
if not os.path.exists(porociloDir):
    os.makedirs(porociloDir)
    print("Generated directory: {}".format(porociloDir))
else:
	print("{} allready exists".format(porociloDir))

doneList = r"\begin{itemize}"+"\n"
willDoList = r"\begin{itemize}"+"\n"
imageNames = []
imageDirectoryPaths = []

for subdir in subdirs:
	currentPerson = ""
	if re.search(r".+/(Jurman)", subdir):
		currentPerson = "Jan Jurman"
		doneList += "\item "+currentPerson+"\n"
		willDoList += "\item "+currentPerson+"\n"
		imageDirectoryPaths.append(subdir+"/")
	elif re.search(r".+/(Hencic)", subdir):
		currentPerson = "Jan Hen\xc4\x8di\xc4\x8d"
		doneList += "\item "+currentPerson+"\n"
		willDoList += "\item "+currentPerson+"\n"
		imageDirectoryPaths.append(subdir+"/")
	elif re.search(r".+/(Kucer)", subdir):
		currentPerson = "Jure Ku\xc4\x8der"	
		doneList += "\item "+currentPerson+"\n"
		willDoList += "\item "+currentPerson+"\n"
		imageDirectoryPaths.append(subdir+"/")
	elif re.search(r".+/(Ruzic)", subdir):
		currentPerson = "Ale\xc5\xa1 Ru\xc5\xbei\xc4\x87"	
		doneList += "\item "+currentPerson+"\n"
		willDoList += "\item "+currentPerson+"\n"
		imageDirectoryPaths.append(subdir+"/")

	files = os.walk(subdir).next()[2] #walk ti da [dirpath, dirnames, filenames]
	for f in files:
		if re.search(r".*?\.(jpg|JPG|PNG|png|jpeg|png)", f):
			if " " in f:
				oldFilePath = subdir + "/" + f
				fileName = f.replace(" ", "_")
				newFilePath = subdir + "/" + fileName
				print ("Renaming {} ~~~> {}".format(oldFilePath, newFilePath))
				os.rename(oldFilePath, newFilePath)
				imageNames.append(fileName)
			else:
				imageNames.append(f)

		elif re.search(r"(porocilo.*\.txt)", f):
			m = re.search(r"(.*porocilo.*\.txt)", f)
			porociloTxtPath = m.group(0)
			# print("~{}".format(subdir+"/"+porociloTxtPath))
			with open(subdir+"/"+porociloTxtPath) as f:
				content = f.readlines()
				content = [x.strip() for x in content] 
				# print(content)
				#position self appropriately
				jeOpravljeno = next(i for i in xrange(len(content)) if "kon\xc4\x8dano" in content[i].lower() or "opravljene naloge" in content[i].lower())
				boOpravljeno = next(i for i in xrange(len(content)) if "naslednji teden" in content[i].lower())
				# print(boOpravljeno)

				#ustvarimo jeOpravljeno list
				personDoneList = r"	\begin{itemize}"+"\n"
				for i in xrange(jeOpravljeno+1, boOpravljeno):
					if content[i] != "":
						#find first character or number
						m = re.search("\d|[a-zA-Z]", content[i])
						if m:
							# print "rx:{}".format(m.start())
							userLine = content[i][:m.start()]
							# print(userLine)
							# print("{}:{}".format(i,r"\item "+content[i]))
							# personDoneList += r"		\item "+content[i]+"\n"
							listIndentLvl = userLine.count("-")
							if listIndentLvl == 0:
								listIndentLvl = 1
							
							personDoneList += "	" * listIndentLvl
							personDoneList += r"\begin{itemize}" * (listIndentLvl-1) +"\n"
							personDoneList += "	" * (listIndentLvl)+r"\item "+content[i][m.start():]+"\n"
							personDoneList += "	" * listIndentLvl
							personDoneList += r"\end{itemize}" * (listIndentLvl-1)  + "\n"
				personDoneList += r"	\end{itemize}"+"\n"
				# print personDoneList
				doneList+=personDoneList

				#ustvarimo boOpravljeno list
				personWillDoList = r"	\begin{itemize}"+"\n"
				naslednjiTeden = content[boOpravljeno+1:]
				if len(naslednjiTeden) != 0:
					for i in xrange(boOpravljeno+1, len(content)):
						if content[i] != "":
							#find first character or number
							m = re.search("\d|[a-zA-Z]", content[i])
							if m:
								# print "rx:{}".format(m.start())
								userLine = content[i][:m.start()]
								# print("{}:{}".format(i,r"\item "+content[i]))
								# personWillDoList += r"		\item "+content[i]+"\n"
								listIndentLvl = userLine.count("-")
								if listIndentLvl == 0:
									listIndentLvl = 1
								personWillDoList += "	" * listIndentLvl + r"\begin{itemize}" * (listIndentLvl-1) +"\n"
								personWillDoList += "	" * listIndentLvl + r"\item "+content[i][m.start():]+"\n"
								personWillDoList += "	" * listIndentLvl + r"\end{itemize}" * (listIndentLvl-1)  + "\n"
				else:
 					personWillDoList += "	" * listIndentLvl + r"\item " + "\xc5\xa0e ni dolo\xc4\x8deno"+"\n"
				personWillDoList += r"	\end{itemize}"+"\n"
				# print personWillDoList
				willDoList+=personWillDoList
		else:
			print f
imageList = []
for imageName in imageNames:
	imageList.append(r"\includegraphics[width=\textwidth,height=\textheight,keepaspectratio]{"+ imageName + r"}\par\vspace{1cm}")
print ("\n".join(imageList))
doneList += r"\end{itemize}"+"\n"
willDoList += r"\end{itemize}"+"\n"

tmpImgPaths = []
for imgPath in imageDirectoryPaths:
	tmpImgPaths.append("/home/jan/Documents/RUPS/Poker/porocila" + imgPath[1:])
imageDirectoryPaths = tmpImgPaths

imageDirectoryPathsString = "{" + "}{".join(imageDirectoryPaths)+"}"
print imageDirectoryPathsString
# print("\n\n\n{}\n\n\n".format(willDoList))

latexFile = open('porociloTemplate', 'r').read()

latexFile = latexFile.replace(r"\ignore{currentPorociloNr}", porociloNr);
latexFile = latexFile.replace(r"\ignore{prevPorociloNr}", str(int(porociloNr)-1));
latexFile = latexFile.replace(r"\ignore{porociloContentDone}", doneList);
latexFile = latexFile.replace(r"\ignore{porociloContentWillDo}", willDoList);
latexFile = latexFile.replace(r"\ignore{porociloContentImages}", "\n".join(imageList));
latexFile = latexFile.replace(r"\ignore{imageDirectories}", imageDirectoryPathsString);

# print latexFile

from latex import build_pdf

# this builds a pdf-file inside a temporary directory
pdf = build_pdf(latexFile)

# look at the first few bytes of the header
print bytes(pdf)[:10]

with open('temp.pdf', 'wb+') as f:
    pdf.save_to("./porocilo.pdf")




#os.walk(directory)
# d = '.'
# [os.path.join(d, o) for o in os.listdir(d) 
# 	if os.path.isdir(os.path.join(d,o))]


#files = [f for f in os.listdir('.') if os.path.isfile(f)]
#for f in files:
#	print(f)