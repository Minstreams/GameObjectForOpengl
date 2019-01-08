#pragma once
class Models {
private:
	static Models* list;
public:
	static Models* List() {
		if (list == NULL) {
			list = new Models();
		}
		return list;
	}
	//以下是表列
	const Model model1 = Model("nanosuit");
	const Model model2 = Model("mazda 3");
	const Model earth = Model("earth");
};

Models* Models::list = NULL;