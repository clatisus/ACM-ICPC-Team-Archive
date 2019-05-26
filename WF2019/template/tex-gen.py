import os

SourceTex = []

chapter = 'DataStructure'

SourceTex.append('\\chapter{' + chapter + '}')
SourceTex.append('')

files = os.listdir(chapter)
for file in files:
    SourceTex.append('\\kactlimport{' + file + '}')

ConfigTex = []

# output to file

with open('chapter.tex', 'w') as Source:
    for x in SourceTex:
        Source.write(x + '\n')
