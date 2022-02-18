template <typename T>
class node {
	T data = NULL;
	node* right_Data = nullptr;
	node* left_Data = nullptr;
	T getMinValue() {
		node* currentNode = this;
		while (currentNode->left_Data != nullptr) {
			currentNode = currentNode->left_Data;
		}
		return currentNode->data;
	}
public:
	node(T datatemp):data(datatemp) {

	}
	node() = default;
	void insert(node&& nodToAdd ) {
		node* currentNode = this;
		if (this->data == NULL && this->left_Data == nullptr && this->right_Data == nullptr) {
			*this = std::move(nodToAdd);
			return;
		}
		else {
			while (true) {
				if (nodToAdd.data <= currentNode->data) {
					if (currentNode->left_Data == nullptr) {
						currentNode->left_Data = &nodToAdd;
						return;
					}
					else {

						currentNode = (currentNode->left_Data);
					}
				}
				else {
					if (currentNode->right_Data == nullptr) {
						currentNode->right_Data = &nodToAdd;
						return;
					}
					else {
						currentNode = (currentNode->right_Data);
					}
				}


			}
				
			
		}

		
	}
	bool search(T value) {
		node* currentNode = this;

		while (currentNode != nullptr) {
			if (value < currentNode->data) {
				currentNode = currentNode->left_Data;

			}
			else {
				if (value > currentNode->data) {
					currentNode = currentNode->right_Data;
				}
				else {
					return true;
				}
			}

		}
		return false;
	}
	void remove(T value_rm, node* parent = nullptr) {
		node* currentNode = this;
		while (currentNode != nullptr) {
			if (value_rm < currentNode->data) {
				parent = currentNode;
				currentNode = currentNode->left_Data;

			}
			else {
				if (value_rm > currentNode->data) {
					parent = currentNode;
					currentNode = currentNode->right_Data;
				}
				else {
					if (currentNode->left_Data && currentNode->right_Data != nullptr) {
						currentNode->data = currentNode->right_Data->getMinValue();
						currentNode->right_Data->remove(currentNode->data, currentNode);
					}
					else {
						if (parent == nullptr) {
							if (currentNode->left_Data != nullptr) {
								currentNode->data = currentNode->left_Data->data;
								currentNode->right_Data = currentNode->left_Data->right_Data;
								currentNode->left_Data = currentNode->left_Data->left_Data;
							}
							else {
								if (currentNode->right_Data != nullptr) {
									currentNode->data = currentNode->right_Data->data;
									currentNode->left_Data = currentNode->right_Data->left_Data;
									currentNode->right_Data = currentNode->right_Data->right_Data;
								}
								else {
									currentNode->data = NULL;
								}
							}

						}
						else {
							if (parent->left_Data == currentNode) {
								if (currentNode->left_Data != nullptr) {
									parent->left_Data = currentNode->left_Data;
								}
								else {
									parent->left_Data = currentNode->right_Data;
								}
							}
							else {
								if (parent->right_Data == currentNode) {
									if (currentNode->left_Data != nullptr) {
										parent->right_Data = currentNode->left_Data;
									}
									else {
										parent->right_Data = currentNode->right_Data;
										return;
									}
								}
							}
						}
					}

				}
				
			}
		}
	}
	
};
