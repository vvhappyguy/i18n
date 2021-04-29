# Script finds files with words from dict(map) 
# and if no file with word exists 
# delete word from dict then save it

import json
import os
import subprocess

SEARCH_PATH="/mnt/d/Projects/.../"
JSON_DICT="/mnt/d/Projects/.../Locales.json"

no_words = []

def grep(word, path):
    cmd = "grep -rn {} {} | grep -v {}"
    cmd = cmd.format(word + ".ru",path,JSON_DICT)
    print(word)
    proc = subprocess.Popen('bash', stdin = subprocess.PIPE, stdout = subprocess.PIPE)
    stdout, stderr = proc.communicate(bytes(cmd, 'utf-8'))
    print(stdout)
    if(len(stdout) == 0):
        no_words.append(word)


with open(JSON_DICT, "r") as read_file:
    data = json.load(read_file)

for key, value in data.items():
    grep(key, SEARCH_PATH)
    # print(key, '->', value)

print(no_words)
for word in no_words:
    data.pop(word)

with open('data.json', 'w', encoding='utf-8') as f:
    json.dump(data, f, ensure_ascii=False, indent=4)
