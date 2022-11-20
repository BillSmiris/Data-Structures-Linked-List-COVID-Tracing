#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

//����� ��� ��� ������������ ��������� ����������.
class Location {
private:
	double lat; //���������� �����
	double lon; //���������� ������

public:
	//default constructor, ����� ��������� ��� �������������
	Location() : lat(0.0), lon(0.0) {

	}
	 //constructor ��� ������ ��� �������������
	Location(double lat, double lon) {
		this->lat = lat;
		this->lon = lon;
	}

	//��������� ��� ������ �� ���������� ������.
	void SetLat(double lat) {
		this->lat = lat;
	}

	//��������� ��� ������ �� ���������� �����.
	void SetLon(double lon) {
		this->lon = lon;
	}

	//��������� ��� ����� �� ���������� ������.
	double GetLat() {
		return lat;
	}

	//��������� ��� ����� �� ���������� �����.
	double GetLon() {
		return lon;
	}

	//��������� ����������� ������� ����������. ������� �� ����������� �� ���������� ��� ������� �������������.
	static Location GenerateRandomLocation(double latLowerBound, double latUpperBound, double lonLowerBound, double lonUpperBound) {
		std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
		std::uniform_real_distribution<double> urdLat(latLowerBound, latUpperBound + 0.0001); //������� ��� ������ ���������� ������.
		std::uniform_real_distribution<double> urdLon(lonLowerBound, lonUpperBound + +0.0001); //������� ��� ������ ���������� �����.
		return Location(urdLat(re), urdLon(re)); //���������� ��� ��������� �� ��� ������� �������������.
	}

	//��������� ��� ������� ��� �������� ������ ��� ����������.
	static double LocationDifference(Location start, Location end) {
		return sqrt(pow(end.GetLat() - start.GetLat(), 2) + pow(end.GetLon() - start.GetLon(), 2)); //��������� ���������� ��������� ��� ����������.
	}

	//��������� ������� ��� ����������� ��� ����������� ������ ��� ����������.
	static int Direction(Location start, Location end){
		double startLat = start.GetLat(); //���������� ������ �������.
		double startLon = start.GetLon(); //���������� ����� �������.
		double endLat = end.GetLat(); //���������� ������ �����.
		double endLon = end.GetLon(); //���������� ����� �����.
		 
		//������� �� ��� �������������, ������������ ���� �������� ��� �������������� ��� ����������.
		if (startLat < endLat && startLon < endLon) {
			return 0; //�������� ������� �����
		}
		else if (startLat > endLat && startLon > endLon) {
			return 1; //�������� ���� ��������
		}
		else if (startLat < endLat && startLon > endLon) {
			return 2; //�������� ������� ��������
		}
		else if (startLat > endLat && startLon < endLon) {
			return 3;//�������� ���� �����
		}
		else if (startLat == endLat && startLon < endLon) {
			return 4; //������ �����
		}
		else if (startLat == endLat && startLon > endLon) {
			return 5; //������ ��������
		}
		else if (startLat < endLat && startLon == endLon) {
			return 6; //������ �������
		}
		else if (startLat > endLat && startLon == endLon) {
			return 7; //������ ����
		}
		return 0;
	}

	//��������� ��� ������� �� ���� ������� ���� ������ ���� ��������� ���, �� ���� ��� ���������� ��� ��� ����������� ���������.
	static bool HasReachedTarget(Location start, Location end, int direction) {
		try {
			if (direction > 7) { //������ �� � ������� ��� ����������� ����� ������.
				throw direction;
			}

			double startLat = start.GetLat();
			double startLon = start.GetLon();
			double endLat = end.GetLat();
			double endLon = end.GetLon();

			if (direction == 0) {
				return startLat < endLat && startLon < endLon;
			}
			else if (direction == 1) {
				return startLat > endLat&& startLon > endLon;
			}
			else if (direction == 2) {
				return startLat < endLat && startLon > endLon;
			}
			else if (direction == 3) {
				return startLat > endLat&& startLon < endLon;
			}
			else if (direction == 4) {
				return startLon < endLon;
			}
			else if (direction == 5) {
				return startLon > endLon;
			}
			else if (direction == 6) {
				return startLat < endLat;
			}
			else if (direction == 7) {
				return startLat > endLat;
			}
			return false;
		}
		catch (int e) {
			std::cout << "Error: Invalid direction parameter.";
			exit(0);
		}
	}
};

//����� ������������� ��������� ������� GPS.
class GPSSignal {
private:
	Location location; //���������
	double timestamp; //������� ������ �������

public:
	//default constructor
	GPSSignal() : location(Location()), timestamp(0){

	};

	//constructor ��� ���������� ����������� �� ����������� ��� ������������� ��� ��� ������� ������
	GPSSignal(int lat, int lon, double timestamp) {
		location = Location(lat, lon);
		this->timestamp = timestamp;
	}

	//constructor ��� ���������� ����������� �� ����������� ��� �������� ��� ��� ������� ������
	GPSSignal(Location location, double timestamp) {
		this->location = location;
		this->timestamp = timestamp;
	}

	//��������� ��� ������ ��� ��������� �� �������������
	void SetLocation(int lat, int lon) {
		location = Location(lat, lon);
	}

	//��������� ��� ������ ��� ��������� �� ����������� ����������
	void SetLocation(Location location) {
		this->location = location;
	}

	//��������� ��� ������ �� ������� ������
	void SetTimestamp(int timestamp) {
		this->timestamp = timestamp;
	}

	//��������� ��� ������ ��� ���������
	Location GetLocation() {
		return location;
	}

	//��������� ��� ������ �� ��������� ��� ����������
	Location* GetLocationRef() {
		return &location;
	}

	//��������� ��� ������ �� ������� ������
	double GetTimestamp() {
		return timestamp;
	}
};

//����� ��� ���������� ��� ����� ���� ����� ������������ ������.
//� ����� ����� template ��� ������ �� ������������ ������� ������������ ����� ���������.
template<typename T>
class Node {
private:
	T data; //�������� ������
	Node<T>* next; //������� �������� ������
	Node<T>* previous; //������� ������������ ������

public:
	//deafult constructor
	Node<T>() : data(NULL), next(NULL), previous(NULL){

	}

	//constructor ��� ������ �� �������� ��� ������
	Node<T>(T data) {
		this->data = data;
		next = NULL; //�� ������� �� ������ �����
		previous = NULL; //�� ������� �� ������ �����
	}

	//��������� ��� ������ �� �������� ���� ������
	void SetData(T data) {
		this->data = data;
	}

	//��������� ��� ������ ��� ������� �����
	void SetNext(Node<T>* next) {
		this->next = next;
	}

	//��������� ��� ������ ��� ����������� �����
	void SetPrevious(Node<T>* previous) {
		this->previous = previous;
	}

	//��������� ��� ������ �� �������� ��� ������
	T GetData() {
		return data;
	}

	//��������� ��� ������ ��������� ��� ��������� ��� ������
	T* GetDataRef() {
		return &data;
	}

	//��������� ��� ������ ��� ������� �����
	Node<T>* GetNext() {
		return next;
	}

	//��������� ��� ������ ��� ������� �����
	Node<T>* GetPrevious() {
		return previous;
	}
};

//����� ��� ���������� ��� ����� ����������� �����
//�� template ����� �� ������������ ������ ������������ ����� ���������
template<typename T>
class DoublyLinkedList {
private:
	Node<T>* start; //������ ������ ������
	Node<T>* end; //���������� ������ ������
	int length; //������� ������

public:
	//constructor, ��������� �� �������, ��� �������� ������ ����� ��� ������
	DoublyLinkedList<T>() : start(NULL), end(NULL), length(0){

	}

	//��������� ��������� ������ ��� �����. ������� �� ��������� �� �������� ��� �� ���� � ������.
	void Insert(T data) {
		if (start) { //�� ������� ������� ������
			Node<T>* currentNode = start; //����� ��� �� ��� ������ �����
			while (currentNode->GetNext()){ //��� ������� �������� ������
				currentNode = currentNode->GetNext(); //���� ��� ������� ����� ��� ��������� �� ��� ������ �����
			}
			currentNode->SetNext(new Node<T>(data)); //���� �� ��� ������� ��� ��������� ������ ��� ��� ����� �� �� ��������
			currentNode->GetNext()->SetPrevious(currentNode); //���� ��� �������� ����� �� ��� ����������� ��� ����
			end = currentNode->GetNext(); //���� �� ��� ����� �� ��� ��������� ��� ������
		}
		else { //������
			start = new Node<T>(data); //���� ���� ��� ����� �� �� �������� �� ��� ������ �����
			end = start; //���� ��� ������ �� ��� ���������
		}
		length++; //������ �� ������� ��� ������
	}

	//��������� ��� ������� ���� ����� ���� ��� ���� ���� ��� ����� �� ���� ��� ������ �����. ������� �� �������� ��� ������ ����� ��� �� �������� ��� ������.
	void InsertBefore(int index, T data) {
		try {
			if (index >= length || index < 0) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			else if (index == 0) { //�� � ������� ����� 0
				Node<T>* newStart = new Node<T>(data); //����������� ��� ��� �����
				start->SetPrevious(newStart); //���� �� ��� ����� �� ��� ����������� ��� ������ ������ ��� ������
				newStart->SetNext(start); //���� ��� ����� ����� ��� ������� ��� ���� 
				start = newStart; //���� �� ��� �� ��� �����
				length++; //������ �� ������� ��� ������ ���� 1
			}
			else { //�� ����������� ���� ���������
				int i; 
				Node<T>* currentNode; //������ ������
				//���������� ����������
				if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
					i = 0; //���� �� i 0
					currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
					while (i < index) { //��� �� i ����� ��������� ��� ������
						currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
						i++; //������ �� i ���� 1
					}
				}
				else { //������
					i = length - 1; //���� �� i ����� ������ - 1
					currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
					while (i > index) { //��� �� i ����� ���������� ��� ������
						currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
						i--; //������ �� i ���� 1
					}
				}
				Node<T>* previous = currentNode->GetPrevious(); //���� ��� ���������� ��� ��������� ������
				Node<T>* newNode = new Node<T>(data); //����������� ��� ��� ����� �� �� ��������
				previous->SetNext(newNode); //���� �� ��� ������� ����� ��� ������������ �� ��� �����
				currentNode->SetPrevious(newNode); //���� �� ��� ����������� ����� ��� ��������� ������ �� ���
				newNode->SetPrevious(previous); //���� �� ����������� ����� ��� ���� ��� ����������� ��� ���������
				newNode->SetNext(currentNode); //���� �� ������� ����� ��� ���� ��� ������
				length++; //������ �� ������� ��� ������ ���� 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	//��������� ��� ������� ���� ����� ���� ��� ���� ���� ��� ����� �� ���� �� ��������� ��� ����� ���� ������. ������� �� �������� �� ���� ��� �������� ������ ��� �� �������� ��� ���� ������.
	void InsertBefore(Node<T>* node, T data) {
		Node<T>* newNode = new Node<T>(data); //����������� ��� ��� ����� �� �� ��������
		Node<T>* previous = node->GetPrevious(); //���� ��� ����������� ��� �������� ������
		if (previous) //�� � ������������ �������
			previous->SetNext(newNode); //���� ��� ������� ��� ������������ �� �� ��� �����
		else //�� ��� �������, �������� ��� � ���� ������ ������������ ���� ���� ��� ������
			start = newNode; //��������, ���� �� ��� ����� �� ��� ����� ��� ������
		node->SetPrevious(newNode); //���� �� ��� ����� �� ��� ����������� ��� ��������
		newNode->SetPrevious(previous); //���� ��� ���������� ��� �������� �� ��� ����������� ��� ����
		newNode->SetNext(node); //���� ��� ������� ����� �� ��� ����������� ��� ����
		length++; //������ �� ������� ��� ������ ���� 1
	}

	//��������� ��� ������� ���� ����� ���� ��� ���� ���� ��� ����� �� ���� �� ��������� ��� ����� ���� ������. ������� �� �������� �� ���� ��� �������� ������ ��� �� �������� ��� ���� ������.
	void InsertAfter(int index, T data) {
		try {
			if (index >= length || index < 0) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			else if (index == length - 1) { //�� � ������� ����� ��� �� ������� ��� ������ + 1
				Node<T>* newEnd = new Node<T>(data); //����������� ��� ��� �����
				end->SetNext(newEnd); //���� �� ��� ����� �� ��� ������� ��� ���������� ������ ��� ������
				newEnd->SetPrevious(end); //���� ��� ��������� ����� ��� ����������� ��� ���� 
				end = newEnd; //���� �� ��� �� ��� ���������
				length++; //������ �� ������� ��� ������ ���� 1
			}
			else { //�� ����������� ���� ���������
				int i;
				Node<T>* currentNode; //������ ������
				//���������� ����������
				if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
					i = 0; //���� �� i 0
					currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
					while (i < index) { //��� �� i ����� ��������� ��� ������
						currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
						i++; //������ �� i ���� 1
					}
				}
				else { //������
					i = length - 1; //���� �� i ����� ������ - 1
					currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
					while (i > index) { //��� �� i ����� ���������� ��� ������
						currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
						i--; //������ �� i ���� 1
					}
				}
				Node<T>* next = currentNode->GetNext(); //���� ��� ������� ��� ��������� ������
				Node<T>* newNode = new Node<T>(data); //����������� ��� ��� ����� �� �� ��������
				next->SetPrevious(newNode); //���� �� ��� ����������� ����� ��� �������� �� ��� �����
				currentNode->SetNext(newNode); //���� �� ��� ������� ����� ��� ��������� ������ �� ���
				newNode->SetNext(next); //���� �� ������� ����� ��� ���� ��� ����������� ��� ���������
				newNode->SetPrevious(currentNode); //���� �� ����������� ����� ��� ���� ��� ������
				length++; //������ �� ������� ��� ������ ���� 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	//��������� ��� ������� ���� ����� ���� ��� ���� ���� ��� ����� �� ���� �� ��������� ��� ����� ���� ������. ������� �� �������� �� ���� ��� �������� ������ ��� �� �������� ��� ���� ������.
	void InsertAfter(Node<T>* node, T data) {
		Node<T>* newNode = new Node<T>(data); //����������� ��� ��� ����� �� �� ��������
		Node<T>* next = node->GetNext(); //���� ��� ������� ��� �������� ������
		if (next) //�� � �������� �������
			next->SetPrevious(newNode); //���� ��� ����������� ��� �������� �� �� ��� �����
		else //�� ��� �������, �������� ��� � ���� ������ ������������ ��� ����� ��� ������
			end = newNode; //��������, ���� �� ��� ����� �� ��� ��������� ��� ������
		node->SetNext(newNode); //���� �� ��� ����� �� ��� ������� ��� ��������
		newNode->SetNext(next); //���� ��� ������� ��� �������� �� ��� ������� ��� ����
		newNode->SetPrevious(node); //���� ��� ������� ����� �� ��� ����������� ��� ����
		length++; //������ �� ������� ��� ������ ���� 1
	}

	//��������� ��� ��������� ��� ��������� ����� ��� ������
	void Delete() {
		try {
			if (!end) { //�� � ����� ����� �����, �������� ������ ������ ��� ��������� �� ���������
				throw 0;
			}
			if (end->GetPrevious()) { //���� � ���������� ������ ���� �����������, ������ � ����� �������� ����������� 2 ��������
				Node<T>* newEnd = end->GetPrevious(); //���������� �� ��������� ��� ������������ ��� ����������
				delete end; //�������� ��� ���������
				end = newEnd; //���� ��� ����������� ��� �� ��� ���������
				end->SetNext(NULL); //���� �� ������ �������� ��� ���� ���������� �� NULL
			}
			else { //�� � ����� ���� ���� ��� �����������
				delete start; //�������� ��� �����
				delete end; //�������� ��� ���������
			}
			length--; //������ �� ����� ��� ������ ���� 1
		}
		catch (int e) {
			std::cout << "Error: List is empty.\n";
			std::exit(1);
		}
	}

	//��������� ��� ��������� ���� ����� ��� ������ �� ���� ��� ������ ��� ����� ��� ��� �����. �������� �� ��������� �� ������ �����
	void Delete(int index) {
		try {
			if (index >= length) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			else if (index == length - 1) { //�� � ������� ����������� ���� ��������� �����
				Delete(); //������ �� ��������� ��������� ��� ����������
			}
			else if (index == 0){ //�� � ������� ����������� ���� ����� �����
				Node<T>* newStart = start->GetNext(); //���������� �� ��������� ��� �������� ��� ������ ������
				if (newStart) //�� �������, ������ �� � ����� ���� ���� ��� ��� ��������
					newStart->SetPrevious(NULL); //���� ���� ��� ����������� ��� ������ ����� �� NULL
				delete start; //�������� ��� �����
				start = newStart; //���� ��� ������� �� ��� �����
				length--; //������ �� ������� ��� ������ ���� 1
			}
			else { //�� ����������� ���� ���������
				int i;
				Node<T>* currentNode; //������ ������
				//���������� ����������
				if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
					i = 0; //���� �� i 0
					currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
					while (i < index) { //��� �� i ����� ��������� ��� ������
						currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
						i++; //������ �� i ���� 1
					}
				}
				else { //������
					i = length - 1; //���� �� i ����� ������ - 1
					currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
					while (i > index) { //��� �� i ����� ���������� ��� ������
						currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
						i--; //������ �� i ���� 1
					}
				}
				Node<T>* next = currentNode->GetNext(); //���������� �� ��������� ��� �������� ��� ��������� ������
				Node<T>* previous = currentNode->GetPrevious(); //���������� �� ��������� ��� ������������ ��� ��������� ������
				next->SetPrevious(previous); //���� �� ��� ����������� ��� �������� ��� ����������� ��� ���������
				previous->SetNext(next); //���� �� ��� ������� ��� ������������ ��� ������� ��� ���������
				delete currentNode; //�������� ��� ������ �����
				length--; //������ �� ������� ��� ������ ���� 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	 //��������� ��� ��������� ���� ����� �� ���� �� ��������� ��� ��� �����. ������� �� ��������� �� ��������� ��� ������.
	void Delete(Node<T>* node) {
		Node<T>* previous = node->GetPrevious(); //���������� ��� ����������� ��� ���� �������� ������
		Node<T>* next = node->GetNext(); //���������� ��� ������� ��� ���� �������� ������
		delete node; //������� ��� �����
		if (previous) //�� � ������������ �������, ������ � ������ �� ����������� ��� ��� ���� ��� ������
			previous->SetNext(next); //���� �� ������� ��� ��� ������� ��� ������������ ������
		if(next) //�� � �������� �������, ������ � ������ �� ����������� ��� �� ����� ��� ������
			next->SetPrevious(previous); //���� �� ����������� ��� ��� ����������� ��� ������������ ������
		length--; //������ �� ������� ��� ������ ���� 1
	}

	//��������� ��������� ��������� ���� ������. �������� �� ������ �� ���� ��� ������ ��� ������ �� �������� ������� �� �����������.
	T GetData(int index) {
		try {
			if (index >= length || index < 0) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			int i;
			Node<T>* currentNode; //������ ������
			//���������� ����������
			if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
				i = 0; //���� �� i 0
				currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
				while (i < index) { //��� �� i ����� ��������� ��� ������
					currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
					i++; //������ �� i ���� 1
				}
			}
			else { //������
				i = length - 1; //���� �� i ����� ������ - 1
				currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
				while (i > index) { //��� �� i ����� ���������� ��� ������
					currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
					i--; //������ �� i ���� 1
				}
			}
			return currentNode->GetData(); //��������� �� �������� ��� ��������� ������
		}
		catch(int e){
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//��������� ��������� ��� ���������� ��� ��������� ���� ������. �������� �� ������ �� ���� ��� ������ ��� ������ �� �������� ������� �� �����������.
	T* GetDataRef(int index) {
		try {
			if (index >= length || index < 0) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			int i;
			Node<T>* currentNode; //������ ������
			//���������� ����������
			if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
				i = 0; //���� �� i 0
				currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
				while (i < index) { //��� �� i ����� ��������� ��� ������
					currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
					i++; //������ �� i ���� 1
				}
			}
			else { //������
				i = length - 1; //���� �� i ����� ������ - 1
				currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
				while (i > index) { //��� �� i ����� ���������� ��� ������
					currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
					i--; //������ �� i ���� 1
				}
			}
			return &currentNode->GetData(); //��������� �� ��������� ��� ��������� ��� ��������� ������
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//��������� ��������� ������ �� ���� �� ���� ��� ��� �����. �������� �� ������ �� ���� ��� ������.
	Node<T>* GetNode(int index) {
		try {
			if (index >= length || index < 0) { //�� � ������� ����� ����� ��� ����� ��� ������
				throw 0; //���� �������� ������ ������ ��� ��������� �� ���������
			}
			int i;
			Node<T>* currentNode; //������ ������
			//���������� ����������
			if (index <= length / 2) { //�� � ������� ������� ����� ��� ���� � ���� �� ���� ��� ������
				i = 0; //���� �� i 0
				currentNode = start; //���� ��� ����� ����� �� ��� ������ �����
				while (i < index) { //��� �� i ����� ��������� ��� ������
					currentNode = currentNode->GetNext(); //���� ���� ������ ����� ��� ������� ���
					i++; //������ �� i ���� 1
				}
			}
			else { //������
				i = length - 1; //���� �� i ����� ������ - 1
				currentNode = end; //���� ��� ��������� ����� �� ��� ������ �����
				while (i > index) { //��� �� i ����� ���������� ��� ������
					currentNode = currentNode->GetPrevious(); //���� ���� ������ ����� ��� ����������� ���
					i--; //������ �� i ���� 1
				}
			}
			return currentNode; //��������� �� ��������� ��� ������
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//��������� ��� ���������� �� ������� ��� ������
	int Length() {
		return length;
	}
};

//��������� ��� ������� ���� ������ ������� ������ ��� ������� �������� ��� ����� ��� ���������� ���.
int RandomInt(int lowerBound, int upperBound) {
	std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_int_distribution<> randomInt(lowerBound, upperBound);
	return randomInt(re);
}

//��������� ��� ������� ���� ������ ������ ������� ������������ ��� ������� �������� ��� ����� ��� ���������� ���.
double RandomDouble(double lowerBound, double upperBound) {
	std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<double> randomDouble(lowerBound, upperBound + 0.0001);
	return randomDouble(re);
}

//����� ��� ���������� ���� ������� ��� ���������.
class User {
private:
	DoublyLinkedList<GPSSignal> trajectory = DoublyLinkedList<GPSSignal>(); //������ ������
	DoublyLinkedList<Node<GPSSignal>*> dayStart = DoublyLinkedList<Node<GPSSignal>*>(); //����� �� ������� ���� ��� ������� ������� ���� �����
	Location location = Location::GenerateRandomLocation(0, 1000, 0, 1000); //�������� ���� ������
	Location target = location; //������ ���������� ������
	double speedms = 0.0; //�������� ������ �� m/s
	double speedY = 0.0; //��������� ��������� ������ ���� ����� y
	double speedX = 0.0; //��������� ��������� ������ ���� ����� x
	bool moving = false; //��������� ��� ������� �� �������� � �������
	bool waiting = false; //��������� ��� ������� �� ��������� � �������
	double waitingTime = 0.0; //������ ��� �� ��������� � �������
	double startWaitingTime = 0.0; //������� ������ ������� ��������
	int direction = 0; //���������� ����������� ������� ������
	bool infected = false; //��������� �������� ������
	bool reached = false; //��������� ��� ������� �� � ������� ���� ������ ���� ��������� ���
	bool signal = true; //��������� ��� ������� �� �� GPS ��� ������ ���� ����
	double* currentTime = NULL; //������� ���� �� ����� ��� ������������
	double signalDownTime = 0.0; //������ ��� ��� ����� �� ����� �� ���� ��� GPS ��� ������
	double signalDownStartTime = 0.0; //������� ������ ��� ������ � ������� �������
	bool nextStart = false; //��������� ��� ������� �� � �������� ������ ��� ������� ��� ������ �� ����� � ������ ���� �����

public:
	//deafult constructor
	User() {

	}

	//constructor ��� ������� �� �������� ��� ��������� ��� �������� ��� ������ ��� �� ��������� ��� �������� ��� ������������
	User(bool infected, double* currentTime) {
		this->infected = infected;
		this->currentTime = currentTime;
	}

	//��������� ��� ������������ �� ����������� ��� ������
	void Simulate() {
		if (signal && RandomInt(0, 9) < 2 ) { //�� �� GPS ���� ����, ��������� �� �� ���� �� ����� �� ���������� �������� 20%
			signalDownTime = RandomInt(0, 10) * 30.0; //������� ������ �� �������� ��� ��������
			signalDownStartTime = *currentTime; //���� ��� �������� ������� ������ ��� ������������ �� �� ������� ������ ��������� ��� ��������
			signal = false; //���� �� ���� false
		}
		else if (!signal && *currentTime - signalDownStartTime >= signalDownTime) { //�� �� GPS ��� ���� ���� ��� ���� ������� � �������� ��������
			signal = true; //���� �� ���� true
		}

		if (moving) { //��� � ������� ��������
			location.SetLat(location.GetLat() + speedY * 30.0); //�������� �� ���� ��� ���� ����� y ���� ��� �������� ��� ���� ����� y ��� 30
			location.SetLon(location.GetLon() + speedX * 30.0); //�������� �� ���� ��� ���� ����� x ���� ��� �������� ��� ���� ����� x ��� 30
			if (!Location::HasReachedTarget(location, target, direction)) { //��� � ������� ���� ������ ���� ��������� ���
				location = target; //���� �� ���� ��� ���������� ��� �� ��� �������� ���� ���
				moving = false; //���� ��� ������ �� false
			}
		}
		else { //�� ��� ��������
			if (!waiting) { //�� ��� ���������
				waitingTime = RandomInt(0, 120) * 30.0; //���� ������� ��� ������ �������� ��������
				if (waitingTime > 0.0) { //�� � �������� ����� ���������� ��� 0
					startWaitingTime = *currentTime; //���� ��� �������� ��� ������������ �� �� ������� ������ ������� ��� ��������
					waiting = true; //���� ��� ������� true
				}
			}
			else if (*currentTime - startWaitingTime >= waitingTime) { //�� � ������� ��������� ��� ���� ������� � ������ ��������
				waiting = false; //���� ��� ������� false
			}

			if (!waiting) { //�� � ������� ��� ���������
				do {
					target = Location::GenerateRandomLocation(0, 1000, 0, 1000); //������� ���� ������ ���������
				} while (location.GetLat() == target.GetLat() && location.GetLon() == target.GetLon()); //������������ ��� ��������� ����������
				speedms = RandomDouble(3.0, 6.0) * 0.27778; //������� ��� �������� ��� 3 ��� 6 km/h ��� �������� �� �� m/s
				direction = Location::Direction(location, target); //���� ��� ���������� ��� ����������� ��� ������
				double dist = Location::LocationDifference(location, target); //���� ��� �������� ������ ��� ��� ����������
				double time = dist / speedms; //���� �� ����� ��� �� ����� � ������� �� ������ ���� ��������� ���
				speedY = (target.GetLat() - location.GetLat()) / time; //���� �� ��������� ��� ��������� ���� ����� y
				speedX = (target.GetLon() - location.GetLon()) / time; //���� �� ��������� ��� ��������� ���� ����� x
				moving = true; //���� ��� ������ �� true
			}
		}

		if (!signal && *currentTime - (int)(*currentTime * (1 / 86400.0)) * 86400.0 == 0){ //�� ��� ������� ���� ��� � �������� ������� ������ ��� ������������ ����������� ���� ���� ���� �����
			nextStart = true; //� �������� ������ �� ����� � ������ ��� �����
		}

		if (signal) { //�� ������� ����
			trajectory.Insert(GPSSignal(location, *currentTime)); //� �������� ���� ��� ������ ���� �� �� ������� ������ ���������� ���� ������
			if (*currentTime - (int)(*currentTime * (1 / 86400.0)) * 86400.0 == 0 || nextStart){ // �� � �������� ������� ������ ��� ������������ ����������� ���� ���� ���� ����� � � �������� ������ ����� � ������ ���� �����
				dayStart.Insert(trajectory.GetNode(trajectory.Length() - 1)); //���� ��� ����� ��� ����� �� ���� ������� ������� ���� �����
				SummarizeTrajectory(dayStart.Length() - 1, 2); //�������� ��� ���������� ������
				if (*currentTime != 0) { //�� �� ��������� �� ��������� ���� ����� ������� ������
					Repair(dayStart.Length() - 2); //����������� �� ������ ������
				}
				nextStart = false; //� �������� ������ �� �� ����� � ������ ���� �����
			}
		}

	}

	//��������� ��� ���������� �� ��������� ��� ������� ��� ������
	DoublyLinkedList<GPSSignal>* GetTrajectory() {
		return &trajectory;
	}

	//��������� ��� ���������� �� ��������� ��� ������ �� ���� ������� ������� ���� �����
	DoublyLinkedList<Node<GPSSignal>*>* GetDayStart() {
		return &dayStart;
	}

	//��������� ��� ����� ��� ��������� �������� ��� ������
	void SetInfectionStatus(bool infected) {
		this->infected = infected;
	}

	//��������� ��� ������ ��� ��������� �������� ��� ������
	bool GetInfectionStatus() {
		return infected;
	}

	//��������� ��� ������������ ��� ������ ���� ����� ��� ������. �������� �� ��������� �� ����.
	//E����������� ��� ������ ��� ������, ������������ �� ��������� ��� ������ ��� ������ �� ��������� 
	//�������� ������� ��� ���������� ��� ���������� ����� ���� ������ ���. 
	void Repair(int day) {
		Node<Node<GPSSignal>*>* utilNode = dayStart.GetNode(day); //���������� ��� ����� ��� �������� ��� ����� ����� ��� �����
		Node<GPSSignal>* startNode = utilNode->GetData(); //���������� ��� ����� ����� ��� �����. �� ���� ������ ������ 2 ������, ����� � ������� �� �������� ��� ����� �������.
		Node<GPSSignal>* endNode; //�� ���� ������ ������ 2 ������, ����� � ������� �� �������� ��� ����� �����.
		Node<GPSSignal>* nextDayNode; //� ������ ������ ��� �������� �����
		double startNodeTime; //������� ������ ������ �����
		double endNodeTime; //������� ������ ������ ������
		Location startNodeLoc; //��������� ������ �����
		Location endNodeLoc; //��������� ������ ������
		double xspeed; //�������� ���� ����� y
		double yspeed; //�������� ���� ����� x
		double timedif; //������� ������� ������ 2 ������
		if (utilNode->GetNext()) { //��� ������� �������� ������ ������ �����
			nextDayNode = utilNode->GetNext()->GetData(); //���������� ���
		}
		else {
			nextDayNode = NULL;
		}
		endNode = startNode->GetNext(); //���� ��� ������� ��� ������ ����� �� ��� �����  �����
		while (endNode != nextDayNode) { //��� ���� ����� ��� ������� ��� �����
			startNodeTime = startNode->GetData().GetTimestamp(); //���������� �� ������� ������ ������ �����
			endNodeTime = endNode->GetData().GetTimestamp(); //���������� �� ������� ������ ������ ������
			startNodeLoc = startNode->GetData().GetLocation(); //���������� ��� ��������� ��� ������ �����
			endNodeLoc = endNode->GetData().GetLocation(); //���������� ��� ��������� ��� ������ �����
			timedif = endNodeTime - startNodeTime; //��������� �� ������� ������� ��� ������
			if (timedif > 30) { //��� � ������� ����� ���������� ��� 30 �������������
				yspeed = (endNodeLoc.GetLat() - startNodeLoc.GetLat()) / timedif * 30; //��������� ��� �������� ���� ����� y
				xspeed = (endNodeLoc.GetLon() - startNodeLoc.GetLon()) / timedif * 30; //��������� ��� �������� ���� ����� x
				int nodesToInsert = timedif / 30 - 1; //��������� ����� ������ ������ �� ���������
				double newLocY = startNodeLoc.GetLat(); //���� y ���� ������
				double newLocX = startNodeLoc.GetLon(); //���� x ���� ������
				double newTime = startNodeTime; //������� ������ ���� ������
				for (int i = 0; i < nodesToInsert; i++) { //��� ����� ������� ������ �� ���������
					//��������� �� �������� ��� ���� ������
					newLocY += yspeed;
					newLocX += xspeed;
					newTime += 30;
					trajectory.InsertBefore(endNode, GPSSignal(newLocY, newLocX, newTime)); //���������� �� ��� ����� ���� ��� ����� �����
				}
			}
			startNode = endNode; //���� ��� ����� ������ �� ��� ����� �����
			endNode = startNode->GetNext(); //���� ��� ������� ����� �� ����� ������
		}
	}

	//��������� ��� ��������� ��� ������ ���� ����� ������� ����� ���� ��� ����.
	//� ��������� ������ ��� ����� ����� ��� ����� ��� ��������� ��� ��� ������ ��� 
	//����� ����� ��������� ��� ������� ���������� ���� �� ��� ������, ��� ���� �� ���� 
	//���� ����� ��� ��������� ����� ��� �������, ���� ����� ��������� ������������� ��� 
	//���������� ��� ��� ����� ����. 
	void SummarizeTrajectory(int day, int daysBefore) {
		if (day - daysBefore >= 0) { //�� � ���� ��� ������ ��� ������ ������� �� ������������� �������
			Node<Node<GPSSignal>*>* utilNode = dayStart.GetNode(day - daysBefore); //���������� ��� ����� ��� �������� ��� ����� ����� ��� �����
			Node<GPSSignal>* centerNode = utilNode->GetData(); //���������� ��� ����� ����� ��� �����. ����� � ������� �� ������� ���� ����� ��� ��������� ��� ������ ��� ������� ���������
			Location centerNodeLocation = centerNode->GetData().GetLocation(); //���������� ��� ��������� ��� ��������� ������
			Node<GPSSignal>* nextDayNode = utilNode->GetNext() ? utilNode->GetNext()->GetData() : NULL; //�� ������� ���������� ��� ����� ����� ��� �������� �����
			Node<GPSSignal>* currentNode = centerNode->GetNext(); //���� ��� ������� ����� ��� ��������� �� ��� ������ ����� ��� ����������
			Location currentLocation; //��������� ��������� ������
			while (centerNode->GetNext() != nextDayNode && centerNode != nextDayNode) { //��� ���� ����� ��� �����
				currentLocation = currentNode->GetData().GetLocation(); //���������� ��� ��������� ��� ��������� ������
				if (Location::LocationDifference(centerNodeLocation, currentLocation) < 50) { //��� � ������ ������ ������ �������� ��� 50 ����� ��� ��� ��������
					trajectory.Delete(currentNode); //�������� ���
				}
				else { //������
					centerNode = currentNode; //���� ��� ������ ����� �� �� ��� ��������
					centerNodeLocation = currentLocation; //���� �� ���� ��� �� �� ��� ��������
				}
				currentNode = centerNode->GetNext(); //���� �� ������ ����� ��� �������
			}
		}
	}
};

struct Utility {
	//��������� ��� ��������� ������� �������� ������������ ��� ������� ���� ������ ��� ��� �������.
	//������� �� ����������� ��� ������, ��� ���� ��� ��� ����� ������� �� ����� � ������� ��� ��� ����� �������
	static bool PossibleCOVID19Infection(User* user, int day, DoublyLinkedList<User>* patients) {
		Node<GPSSignal>* currentUserTrajectoryNode; //������ ������ ��� ������� ��� ������
		Node<GPSSignal>* userNextDayStart = NULL; //������ ������ �������� �����
		if (user->GetDayStart()->GetNode(day)->GetNext()) { // ��� �������, ���������� ��� ����� ����� ��� �������� �����
			userNextDayStart = user->GetDayStart()->GetNode(day)->GetNext()->GetData();
		}
		Node<User>* currentPatientNode = patients->GetNode(0); //���������� ��� ����� ������ ��� �� �����. � ������� ����� �� ����� ��� ������ ��� ����������� �� �� ������
		Node<GPSSignal>* currentPatientTrajectoryNode; //������ ��������� ������
		Node<GPSSignal>* currentPatientNextDayStart; //������ ������ ��� �������� ����� ��� ������� ��� ������
		Location currentPatientLocation; //�������� ��������� ������
		bool nearPatient = false; //��������� ��� ������� �� � ������� ��������� ����� ���� ������
		bool breakOnNext = false; 
		double timeNearPatient = 0.0; //������ ��� ��������� ����� ���� ������
		double currentPatientTime; //������� ������ ���������� ������
		while (currentPatientNode) { //��� ���� ������ ��� ����� �������
			if (currentPatientNode->GetData().GetInfectionStatus()) { //�� � ������� ����� ����������
				currentPatientTrajectoryNode = currentPatientNode->GetData().GetDayStart()->GetData(day); //���������� ��� ���� ��� ������� ��� ������ ��� �� ����
				currentPatientNextDayStart = NULL;
				if (currentPatientNode->GetData().GetDayStart()->GetNode(day)->GetNext()) { //�� �������, ���������� ��� ����� ����� ��� �������� ����� ��� ������� ��� ������
					currentPatientNextDayStart = currentPatientNode->GetData().GetDayStart()->GetNode(day)->GetNext()->GetData();
				}
				while (currentPatientTrajectoryNode != currentPatientNextDayStart) { //��� ���� ����� ���� ������ ��� ������ ��� ��� �����
					currentUserTrajectoryNode = user->GetDayStart()->GetData(day); //���������� ��� ����� ����� ��� ������ ��� ������� ��� ������
					currentPatientLocation = currentPatientTrajectoryNode->GetData().GetLocation(); //���������� ��� �������� ���� ��� ��������� ������
					currentPatientTime = currentPatientTrajectoryNode->GetData().GetTimestamp(); //���������� ��� �������� ������� ������ ��� ��������� ������
					while (currentUserTrajectoryNode) { //��� ���� ����� ��� ������� ��� ������
						//�� � ������� ������� �� ���� 2 ���� ���� ��� �� ���� ���� ����� ��� ��� �������� ��������� ��� ������
						if (std::abs(currentPatientTime - currentUserTrajectoryNode->GetData().GetTimestamp()) <= 7200 && std::abs(Location::LocationDifference(currentPatientLocation, currentUserTrajectoryNode->GetData().GetLocation())) <= 3.0) {
							if (!nearPatient) { //���� �� �� ��������� ����� ���� ������
								nearPatient = true; //���� ���������
							}
							else { //������ �� ���� ��� ����� ���� ������
								//������ �� ����� ��� ��������� ����� ���� ������ ���� �� ������� ������� ��� ��������� ����� ��� �� ��� �����������
								timeNearPatient += currentUserTrajectoryNode->GetData().GetTimestamp() - currentUserTrajectoryNode->GetPrevious()->GetData().GetTimestamp();
								if (timeNearPatient >= 1800) { //�� � ������ ����� ����������� ���� ���
									return true; //���� ��������� true, ����� � ������� ���� ������� ��������
								}
								if (currentUserTrajectoryNode == userNextDayStart) { //�� � ������ ������ ��� ������ ����� � ������ ������ ��� �������� �����
									breakOnNext = true; //������� ��� ������ ��� ��� ������ ������ ���� � ������� ������������ ��� �����
								}
							}
						}
						else { //�� �� ��������� ����� ���� ������
							if (breakOnNext) //������� ��� ������ ��� ��� ������ �� ����������. �� ���� ��� ����� � ������� ������ �� ��������� ��� ��� ������� ����,�� � ������� ��������� ����� ���� ������ ��� ����� ��� ������������
								break;
							timeNearPatient = 0.0; //���� ��� ��� ����� ���� ������ �� 0
							nearPatient = false; //� ������� �� ��������� ����� ���� ������
						}
						currentUserTrajectoryNode = currentUserTrajectoryNode->GetNext(); //���� � ������ ����� ��� ������� ��� ������ ��� �������
					}
					currentPatientTrajectoryNode = currentPatientTrajectoryNode->GetNext(); //���� �� ������ ����� ��� ������� ��� ��������� ������ ��� �������
				}
			}
			currentPatientNode = currentPatientNode->GetNext(); //���� �� ������ ������ ��� �������
		}
		return false; //��������� false �� �� ������� ������ ������ �������
	}

	//��������� ��� ������� ����� ������ ���������� �� ��� ������� �� ��� ������� �������� ���� ����� ��� ����������� ������ �����.
	//� ��������� �������� �� ����������� �� ����, ��������� ��� �������� ������������� ��� �����, �� �������� ������� �������� ��� ��� ����� �������
	static int FindCrowdedPlaces(int day, double startTime, double endTime, double lowerBoundLat, double loweBoundLon, double upperBoundLat, double upperBoundLon, double minimumStayDuration, DoublyLinkedList<User>* users) {
		int usersInArea = 0; //����� ������� �������� ���� �������
		startTime += 86400.0 * day; //������� �������� ������� ������
		endTime += 86400.0 * day; //������� ������� ������� ������
		Node<GPSSignal>* currentTrajectoryNode; //������ ������ ������� ��������� ������
		Node<GPSSignal>* nextDayNode; //������ ������ �������� �����
		Node<Node<GPSSignal>*>* utilNode; //������ ��� �������� ��� ����� ����� ��� �����
		double currentLat; //������ ���������� ������
		double currentLon; //������ ���������� �����
		double currentTimestamp; //�������� ������� ������
		Node<GPSSignal>* inAreaStartNode = NULL; //������ ������� ��� � ������� ������� ���� �������
		bool inArea = false; //��������� ��� ������� �� � ������� ��������� ��� �������

		for (int i = 0; i < users->Length(); i++) { //��� ���� ������
			utilNode = users->GetNode(i)->GetData().GetDayStart()->GetNode(day); //���������� ��� ����� ��� �������� ��� ����� ����� ��� �����
			currentTrajectoryNode = utilNode->GetData(); //���������� ��� ����� ����� ��� �����. ����� � ������ �� ������� ��� ������ ����� ��� ������� ��� ������
			nextDayNode = utilNode->GetNext() ? utilNode->GetNext()->GetData() : NULL; //���������� ��� ����� ��� �������� �����, �� �������
			while (currentTrajectoryNode != nextDayNode) { //��� ���� ����� ��� ������� ��� ������
				currentLat = currentTrajectoryNode->GetData().GetLocation().GetLat(); //���������� �� ���������� ������
				currentLon = currentTrajectoryNode->GetData().GetLocation().GetLon(); //���������� �� ���������� �����
				currentTimestamp = currentTrajectoryNode->GetData().GetTimestamp(); //���������� �� ������� ������
				//�� � �������� ���� ��� ������ ��������� ���� ������� ��� ����������� ������� �������� ��� ������� �������� ������
				if (currentTimestamp >= startTime && currentTimestamp <= endTime && currentLat >= lowerBoundLat && currentLat <= upperBoundLat && currentLon >= loweBoundLon && currentLon <= upperBoundLon && currentTrajectoryNode->GetNext() != nextDayNode) {
					if (!inArea) { //�� � ������� �� ��������� ��� ��� �������
						inAreaStartNode = currentTrajectoryNode; //���� ��� ������ ����� �� ��� ����� �������
						inArea = true; //� ������� ��������� ���� �������
					}
				}
				else { //�� � �������� ��������� ����� ����� ��������
					if (inArea) { //�� � ������� ��������� ��� ���� �������
						inArea = false; //� ������� �� ��������� ���� �������
						//�� � ������� ��������� ��� ����������� ��� �������� ���������� ����� ���� �������
						if (currentTrajectoryNode->GetPrevious()->GetData().GetTimestamp() - inAreaStartNode->GetData().GetTimestamp() >= minimumStayDuration) {
							usersInArea++; //������ �� ������ ��� ������� ���� ������� ���� 1
							break; //������� ���� ������ ��� �������� ������
						}
					}
				}
				currentTrajectoryNode = currentTrajectoryNode->GetNext(); //���� ��� ������� ����� ��� ������� �� ��� ������
			}
		}

		return usersInArea; //��������� �� ������ ��� ������� ���� �������
	}
};

//����� ��������
int main()
{
	double currentTime = 0.0; //����� ������������
	DoublyLinkedList<User> users = DoublyLinkedList<User>(); //����� �������
	//�������� 12 ������� ��� �����. �� ��� ��� ������ ����� ����������
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(true, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(true, &currentTime));
	users.Insert(User(false, &currentTime));
	users.Insert(User(false, &currentTime));

	Node<User>* userNodeToCheck; //������ ������ ��� ��� ����� ������ �� ���������� ������ ��������
	User* userToCheck; //������� ��� ��� ����� ������ �� ���������� ������ ��������
	bool yesNoControl = false; //input ���������/�������
	//inputs ��� ��� �������� ��� FindCrowdedPlaces ��� �� �����������
	int lowerLatBound;
	int upperLatBound;
	int lowerLonBound;
	int upperLonBound;
	int lowerTimeBound;
	int upperTimeBound;
	int minimumStayDuration;

	//������� ������������
	while (true) {
		for (int i = 0; i < users.Length(); i++) { //��� ���� ������
			users.GetNode(i)->GetDataRef()->Simulate(); //����������� �� ����������� ���
		}
		if (currentTime != 0 && currentTime - (int)(currentTime * (1 / 86400.0)) * 86400.0 == 0) { //�� � ������ ������������ ��� ����� ����� ��� ����������� ���� ���� ������� �����
			userNodeToCheck = users.GetNode(0); //���������� ��� ����� ��� ������ ������
			while (userNodeToCheck) { //��� ���� ������
				userToCheck = userNodeToCheck->GetDataRef(); //���������� �� �����
				//�� ��� ����� ����������, ������ �� ������� ��������� ���� ���� ����������� ����
				if (!userToCheck->GetInfectionStatus() && userToCheck->GetDayStart()->Length() - 2 >= 0 && Utility::PossibleCOVID19Infection(userToCheck, userToCheck->GetDayStart()->Length() - 2, &users)) {
					std::cout << "New possible infection\n"; //�� ������� ������ �������, �������� ������ �����������
					userToCheck->SetInfectionStatus(true); //��� ���� ��� ��������� �������� ��� �� true
				}
				userNodeToCheck = userNodeToCheck->GetNext(); //���� ��� ������� ������ �� ������
			}
			//���� � ���� ��������, ���� �� ������ �� ����� �� ��� �� ������ ������� ���� ���� �����
			std::cout << "Day complete.\nWould you like to search for crowded areas?\nyes(1)	no(0)\n";
			std::cin >> yesNoControl;
			if (yesNoControl) {
				//������ ��� ����������� ��� ���������� ��� �� ������
				std::cout << "Enter minimum time of day: ";
				std::cin >> lowerTimeBound;
				std::cout << "\nEnter maximum time of day: ";
				std::cin >> upperTimeBound;
				std::cout << "\nEnter mimimum latitude: ";
				std::cin >> lowerLatBound;
				std::cout << "\nEnter minimum longitude: ";
				std::cin >> lowerLonBound;
				std::cout << "\nEnter maximum latitude: ";
				std::cin >> upperLatBound;
				std::cout << "\nEnter maximum longitude: ";
				std::cin >> upperLonBound;
				std::cout << "\nEnter minimum stay duration: ";
				std::cin >> minimumStayDuration;
				//�������� �� FindCrowdedPlaces ��� �������� �� ����������
				std::cout << "\nUsers in area: " << Utility::FindCrowdedPlaces(users.GetData(0).GetDayStart()->Length() - 2, lowerTimeBound, upperTimeBound, lowerLatBound, lowerLonBound, upperLatBound, upperLonBound, minimumStayDuration, &users) << std::endl << std::endl;
			}
			//���� �� ������ �� ����� �� ���� ��� �� ��������
			std::cout << "Exit program?\nyes(1)		no(0)\n";
			std::cin >> yesNoControl;
			if (yesNoControl) {
				break;
			}
		}
		currentTime += 30.0; //������ �� ������ ��� ������ ���� 30
	}
} 
