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

    def __init__(self, remapping = "phoneremapping.json", cmu_dictionary = None):
        self.dict = load(open(remapping))
        self.word_to_phoneme = cmu_dictionary
        self.labels = {}
        self.num_labels = 0
        self.build_labels()
        

    def remap(self, word):
        phonemes = self.word_to_phoneme.get_phonemes(word)
        lst = []
        for phoneme in phonemes:
            phone = "".join([letter for letter in phoneme if not letter.isdigit()])
            lst.append(self.dict[phone])
        return lst
    
    def build_labels(self):
        for v in self.dict:
            if self.dict[v] in self.labels:
                continue
            self.num_labels += 1    
            self.labels[self.dict[v]] = self.num_labels
            
    def remap_for_training(self,word):
        lst = self.remap(word)
        return self.collapse_similar_values([self.labels[lbl] for lbl in lst])
    
    def collapse_similar_values(self, lst):
        #TODO: Investigate if needed when using CTC
        new_lst = []
        for item in lst:
            if len(new_lst) == 0:
                new_lst = [item]
                continue
            if new_lst[-1] == item:
                continue
            new_lst.append(item)
        return new_lst