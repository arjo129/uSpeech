from json import load

class CMUDictParser:
    
    def __init__(self, file_path = "cmudict-0.7b.txt"):
        self.file_path = file_path
        self.dictionary = {}
        with open(self.file_path) as file:
            for line in file:
                if line[0] == ";":
                    continue
                line = line.replace("\n","")
                split = line.split(" ")
                self.dictionary[split[0]] = list(filter(lambda x: x != "", split[1:]))
    
    def get_phonemes(self, word):
        return self.dictionary[word.upper()]

class PhonemeRemapper:

    def __init__(self, remapping = "phoneremapping.json", cmu_dictionary = CMUDictParser()):
        self.dict = load(open(remapping))
        self.word_to_phoneme = cmu_dictionary
        self.labels = {}
        self.build_labels()

    def remap(self, word):
        phonemes = self.word_to_phoneme.get_phonemes(word)
        lst = []
        for phoneme in phonemes:
            phone = "".join([letter for letter in phoneme if not letter.isdigit()])
            lst.append(self.dict[phone])
        return lst
    
    def build_labels(self):
        i = 0
        for _, v in self.dict:
            if v in self.labels:
                continue
            self.labels[v] = i
            i += 1 