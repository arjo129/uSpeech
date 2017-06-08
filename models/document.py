class Document:
	def __init__(self, data, markers):
		self.data = data
		self.markers =  markers
	def generate_training_array():
		vec_size = len(self.data[0])
		for row in self.data:
			if len(row) != vec_size: raise Exception("Sorry, lengths")
