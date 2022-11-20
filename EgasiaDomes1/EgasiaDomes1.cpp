#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

//Κλάση για την αναπαράσταση δεδομένων τοποθεσίας.
class Location {
private:
	double lat; //γεωγραφικό μήκος
	double lon; //γεωγραφικό πλάτος

public:
	//default constructor, απλως μηδενίζει τις συντεταγμένες
	Location() : lat(0.0), lon(0.0) {

	}
	 //constructor που ορίζει τις συντεταγμένες
	Location(double lat, double lon) {
		this->lat = lat;
		this->lon = lon;
	}

	//Συνάρτηση που ορίζει το γεωγραφικό πλάτος.
	void SetLat(double lat) {
		this->lat = lat;
	}

	//Συνάρτηση που ορίζει το γεωγραφικό μήκος.
	void SetLon(double lon) {
		this->lon = lon;
	}

	//Συνάρτηση που θέτει το γεωγραφικό πλάτος.
	double GetLat() {
		return lat;
	}

	//Συνάρτηση που θέτει το γεωγραφικό μήκος.
	double GetLon() {
		return lon;
	}

	//Συνάρτηση δημιουργίας τυχαίας τοποθεσίας. Δέχεται ως παραμέτρους τα διαστήματα των πιθανών συντεταγμένων.
	static Location GenerateRandomLocation(double latLowerBound, double latUpperBound, double lonLowerBound, double lonUpperBound) {
		std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
		std::uniform_real_distribution<double> urdLat(latLowerBound, latUpperBound + 0.0001); //Παράγει ένα τυχαίο γεωγραφικό πλάτος.
		std::uniform_real_distribution<double> urdLon(lonLowerBound, lonUpperBound + +0.0001); //Παράγει ένα τυχαίο γεωγραφικό μήκος.
		return Location(urdLat(re), urdLon(re)); //Επιστρέφει την τοποθεσία με τις τυχαίες συντεταγμένες.
	}

	//Συνάρτηση που βρίσκει την απόσταση μεταξύ δύο τοποθεσιών.
	static double LocationDifference(Location start, Location end) {
		return sqrt(pow(end.GetLat() - start.GetLat(), 2) + pow(end.GetLon() - start.GetLon(), 2)); //Επιστροφή ευκλείδιας απόστασης δύο τοποθεσιών.
	}

	//Συνάρτηση εύρεσης της κατεύθυνσης του διανύσματος μεταξύ δύο τοποθεσιών.
	static int Direction(Location start, Location end){
		double startLat = start.GetLat(); //Γεωγραφικό πλάτος έναρξης.
		double startLon = start.GetLon(); //Γεωγραφικό μήκος έναρξης.
		double endLat = end.GetLat(); //Γεωγραφικό πλάτος λήξης.
		double endLon = end.GetLon(); //Γεωγραφικό μήκος λήξης.
		 
		//Ανάλογα με τις συντεταγμένες, επιστρέφεται ένας ακαίρεος που αντιπροσωπεύει την κατεύθυνση.
		if (startLat < endLat && startLon < endLon) {
			return 0; //Διαγώνια μπροστά δεξιά
		}
		else if (startLat > endLat && startLon > endLon) {
			return 1; //Διαγώνια πίσω αριστερά
		}
		else if (startLat < endLat && startLon > endLon) {
			return 2; //Διαγώνια μπροστά αριστερά
		}
		else if (startLat > endLat && startLon < endLon) {
			return 3;//Διαγώνια πίσω δεξιά
		}
		else if (startLat == endLat && startLon < endLon) {
			return 4; //Ευθεία δεξιά
		}
		else if (startLat == endLat && startLon > endLon) {
			return 5; //Ευθεία αριστερά
		}
		else if (startLat < endLat && startLon == endLon) {
			return 6; //Ευθεία μπροστά
		}
		else if (startLat > endLat && startLon == endLon) {
			return 7; //Ευθεία πίσω
		}
		return 0;
	}

	//Συνάρτηση που ελέγχει αν ένας χρήστης έχει φτάσει στον προορισμό του, με βάση μία κατεύθυνση από την προηγούμενη συνάρτηση.
	static bool HasReachedTarget(Location start, Location end, int direction) {
		try {
			if (direction > 7) { //Έλεχος αν ο αριθμός της κατεύθυνσης είναι σωστός.
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

//Κλάση αναπαράστασης δεδομένων σημάτων GPS.
class GPSSignal {
private:
	Location location; //τοποθεσία
	double timestamp; //χρονική στιγμή σήματος

public:
	//default constructor
	GPSSignal() : location(Location()), timestamp(0){

	};

	//constructor που δημιουργεί αντικείμενο με παραμέτρους τις συντεταγμένες και μια χρονική στιγμή
	GPSSignal(int lat, int lon, double timestamp) {
		location = Location(lat, lon);
		this->timestamp = timestamp;
	}

	//constructor που δημιουργεί αντικείμενο με παραμέτρους μια τοποθσία και μια χρονική στιγμή
	GPSSignal(Location location, double timestamp) {
		this->location = location;
		this->timestamp = timestamp;
	}

	//Συνάρτηση που ορίζει την τοποθεσία με συντεταγμένες
	void SetLocation(int lat, int lon) {
		location = Location(lat, lon);
	}

	//Συνάρτηση που ορίζει την τοποθεσία με αντικείμενο τοποθεσίας
	void SetLocation(Location location) {
		this->location = location;
	}

	//Συνάρτηση που ορίζει τη χρονική στιγμή
	void SetTimestamp(int timestamp) {
		this->timestamp = timestamp;
	}

	//Συνάρτηση που ανακτά την τοποθεσία
	Location GetLocation() {
		return location;
	}

	//Συνάρτηση που ανακτά τη διεύθυνση της τοποθεσίας
	Location* GetLocationRef() {
		return &location;
	}

	//Συνάρτηση που ορίζει τη χρονική στιγμή
	double GetTimestamp() {
		return timestamp;
	}
};

//Κλάση που αναπαριστά τον κόμβο μιας διπλά συνδεδεμένης λίστας.
//Η κλαση είναι template και μπορεί να δημιουργήσει κόμβους οποιουδήποτε τύπου δεδομένων.
template<typename T>
class Node {
private:
	T data; //δεδομένα κόμβου
	Node<T>* next; //δείκτης επόμενου κόμβου
	Node<T>* previous; //δείκτης πεοηγούμενου κόμβου

public:
	//deafult constructor
	Node<T>() : data(NULL), next(NULL), previous(NULL){

	}

	//constructor που ορίζει τα δεδομένα του κόμβου
	Node<T>(T data) {
		this->data = data;
		next = NULL; //δε δείχνει σε κάποιο κόμβο
		previous = NULL; //δε δείχνει σε κάποιο κόμβο
	}

	//Συνάρτηση που ορίζει τα δεδομένα ενός κόμβου
	void SetData(T data) {
		this->data = data;
	}

	//Συνάρτηση που ορίζει τον επόμενο κόμβο
	void SetNext(Node<T>* next) {
		this->next = next;
	}

	//Συνάρτηση που ορίζει τον προηγούμενο κόμβο
	void SetPrevious(Node<T>* previous) {
		this->previous = previous;
	}

	//Συνάρτηση που ανακτά τα δεδομένα του κόμβου
	T GetData() {
		return data;
	}

	//Συνάρτηση που ανακτά διεύθυνση των δεδομένων του κόμβου
	T* GetDataRef() {
		return &data;
	}

	//Συνάρτηση που ανακτά τον επόμενο κόμβο
	Node<T>* GetNext() {
		return next;
	}

	//Συνάρτηση που ανακτά τον επόμενο κόμβο
	Node<T>* GetPrevious() {
		return previous;
	}
};

//Κλάση που αναπαριστά μια διπλά συνδεδεμένη λίστα
//Ως template μορεί να δημιουργήσει λίστες οποιουδήποτε τύπου δεδομένων
template<typename T>
class DoublyLinkedList {
private:
	Node<T>* start; //Πρώτος κόμβος λίστας
	Node<T>* end; //Τελευταίος κόμβος λίστας
	int length; //Μέγεθος λίστας

public:
	//constructor, μηδενίζει το μέγεθος, δεν υπάρχουν κόμβοι αρχής και τέλους
	DoublyLinkedList<T>() : start(NULL), end(NULL), length(0){

	}

	//Συνάρτηση εισαγωγής κόμβου στη λίστα. Δέχεται ως παράμετρο τα δεδομένα που θα έχει ο κόμβος.
	void Insert(T data) {
		if (start) { //Αν υπάρχει αρχικός κόμβος
			Node<T>* currentNode = start; //όρισε τον ως τον τρέχον κόμβο
			while (currentNode->GetNext()){ //όσο υπάρχει επόμενος κόμβος
				currentNode = currentNode->GetNext(); //θέσε τον επόμενο κόμβο του τρέχοντος ως τον τρέχον κόμβο
			}
			currentNode->SetNext(new Node<T>(data)); //θέσε ως τον επόμενο του τρέχοντος κόμβου ένα νέο κόμβο με τα δεδομένα
			currentNode->GetNext()->SetPrevious(currentNode); //θέσε τον τρέχοντα κόμβο ως τον προηγούμενο του νέου
			end = currentNode->GetNext(); //θέσε το νέο κόμβο ως τον τελευταίο της λίστας
		}
		else { //αλλιώς
			start = new Node<T>(data); //θέσε έναν νέο κόμβο με τα δεδομένα ως τον αρχικό κόμβο
			end = start; //θεσε τον αρχικό ως τον τελευταίο
		}
		length++; //αύξησε το μέγεθος της λίστας
	}

	//Συνάρτηση που εισάγει έναν κόμβο πριν από έναν άλλο στη λίστα με βάση ένα δείκτη θέσης. Παίρνει ως ορίσματα τον δείκτη θέσης και τα δεδομένα του κόμβου.
	void InsertBefore(int index, T data) {
		try {
			if (index >= length || index < 0) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			else if (index == 0) { //Αν ο δείκτης είναι 0
				Node<T>* newStart = new Node<T>(data); //δημιούργησε ένα νέο κόμβο
				start->SetPrevious(newStart); //θέσε το νέο κόμβο ως τον προηγούμενο του πρώτου κόμβου της λίστας
				newStart->SetNext(start); //θέσε τον πρώτο κόμβο τον επόμενο του νέου 
				start = newStart; //θέσε το νέο ως τον πρώτο
				length++; //αύξησε το μέγεθος της λίστας κατά 1
			}
			else { //Σε οποιαδήποτε άλλη περίπτωση
				int i; 
				Node<T>* currentNode; //τρέχον κόμβος
				//διαδικασία αναζήτησης
				if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
					i = 0; //θέσε το i 0
					currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
					while (i < index) { //όσο το i είναι μικρότερο του δείκτη
						currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
						i++; //αύξησε το i κατά 1
					}
				}
				else { //αλλιώς
					i = length - 1; //θέσε το i μήκος λίστας - 1
					currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
					while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
						currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
						i--; //μείωσε το i κατά 1
					}
				}
				Node<T>* previous = currentNode->GetPrevious(); //πάρε τον πρηγούμενο του τρέχοντος κόμβου
				Node<T>* newNode = new Node<T>(data); //δημιούργησε ένα νέο κόμβο με τα δεδομένα
				previous->SetNext(newNode); //θέσε ως τον επόμενο κόμβο του προηγούμενου το νέο κόμβο
				currentNode->SetPrevious(newNode); //θέσε ως τον προηγούμενο κόμβο του τρέχοντος κόμβου το νέο
				newNode->SetPrevious(previous); //θέσε ως προηγούμενο κόμβο του νέου τον προηγούμενο του τρέχοντος
				newNode->SetNext(currentNode); //θέσε ως επόμενο κόμβο του νέου τον τρέχον
				length++; //αύξησε το μέγεθος της λίστας κατά 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	//Συνάρτηση που εισάγει έναν κόμβο πριν από έναν άλλο στη λίστα με βάση τη διεύθυνση στη μνήμη ενός κόμβου. Παίρνει ως ορίσματα τη θέση του υπαρκτού κόμβου και τα δεδομένα του νέου κόμβου.
	void InsertBefore(Node<T>* node, T data) {
		Node<T>* newNode = new Node<T>(data); //δημιούργησε ένα νέο κόμβο με τα δεδομένα
		Node<T>* previous = node->GetPrevious(); //πάρε τον προηγούμενο του υπαρκτού κόμβου
		if (previous) //αν ο προηγούμενος υπάρχει
			previous->SetNext(newNode); //θέσε τον επόμενο του προηγούμενου ως το νέο κόμβο
		else //αν δεν υπάρχει, σημαίνει ότι ο νέος κόμβος τοποθετείται στην αρχή της λίστας
			start = newNode; //επομένως, θέσε το νέο κόμβο ως τον πρώτο της λίστας
		node->SetPrevious(newNode); //θέσε το νέο κόμβο ως τον προηγούμενο του υπαρκτού
		newNode->SetPrevious(previous); //θέσε τον προγούμενο του υπαρκτού ως τον προηγούμενο του νέου
		newNode->SetNext(node); //θέσε τον υπαρκτό κόμβο ως τον προηγούμενο του νέου
		length++; //αύξησε το μέγεθος της λίστας κατά 1
	}

	//Συνάρτηση που εισάγει έναν κόμβο μετά από έναν άλλο στη λίστα με βάση τη διεύθυνση στη μνήμη ενός κόμβου. Παίρνει ως ορίσματα τη θέση του υπαρκτού κόμβου και τα δεδομένα του νέου κόμβου.
	void InsertAfter(int index, T data) {
		try {
			if (index >= length || index < 0) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			else if (index == length - 1) { //Αν ο δείκτης είναι όσο το μέγεθος της λίστας + 1
				Node<T>* newEnd = new Node<T>(data); //δημιούργησε ένα νέο κόμβο
				end->SetNext(newEnd); //θέσε το νέο κόμβο ως τον επόμενο του τελευταίου κόμβου της λίστας
				newEnd->SetPrevious(end); //θέσε τον τελευταίο κόμβο τον προηγούμενο του νέου 
				end = newEnd; //θέσε το νέο ως τον τελευταίο
				length++; //αύξησε το μέγεθος της λίστας κατά 1
			}
			else { //Σε οποιαδήποτε άλλη περίπτωση
				int i;
				Node<T>* currentNode; //τρέχον κόμβος
				//διαδικασία αναζήτησης
				if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
					i = 0; //θέσε το i 0
					currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
					while (i < index) { //όσο το i είναι μικρότερο του δείκτη
						currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
						i++; //αύξησε το i κατά 1
					}
				}
				else { //αλλιώς
					i = length - 1; //θέσε το i μήκος λίστας - 1
					currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
					while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
						currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
						i--; //μείωσε το i κατά 1
					}
				}
				Node<T>* next = currentNode->GetNext(); //πάρε τον επόμενο του τρέχοντος κόμβου
				Node<T>* newNode = new Node<T>(data); //δημιούργησε ένα νέο κόμβο με τα δεδομένα
				next->SetPrevious(newNode); //θέσε ως τον προηγούμενο κόμβο του επόμενου το νέο κόμβο
				currentNode->SetNext(newNode); //θέσε ως τον επόμενο κόμβο του τρέχοντος κόμβου το νέο
				newNode->SetNext(next); //θέσε ως επόμενο κόμβο του νέου τον προηγούμενο του τρέχοντος
				newNode->SetPrevious(currentNode); //θέσε ως προηγούμενο κόμβο του νέου τον τρέχον
				length++; //αύξησε το μέγεθος της λίστας κατά 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	//Συνάρτηση που εισάγει έναν κόμβο μετά από έναν άλλο στη λίστα με βάση τη διεύθυνση στη μνήμη ενός κόμβου. Παίρνει ως ορίσματα τη θέση του υπαρκτού κόμβου και τα δεδομένα του νέου κόμβου.
	void InsertAfter(Node<T>* node, T data) {
		Node<T>* newNode = new Node<T>(data); //δημιούργησε ένα νέο κόμβο με τα δεδομένα
		Node<T>* next = node->GetNext(); //πάρε τον επόμενο του υπαρκτού κόμβου
		if (next) //αν ο επόμενος υπάρχει
			next->SetPrevious(newNode); //θέσε τον προηγούμενο του επόμενου ως το νέο κόμβο
		else //αν δεν υπάρχει, σημαίνει ότι ο νέος κόμβος τοποθετείται στο τέλος της λίστας
			end = newNode; //επομένως, θέσε το νέο κόμβο ως τον τελευταίο της λίστας
		node->SetNext(newNode); //θέσε το νέο κόμβο ως τον επόμενο του υπαρκτού
		newNode->SetNext(next); //θέσε τον επόμενο του υπαρκτού ως τον επόμενο του νέου
		newNode->SetPrevious(node); //θέσε τον υπαρκτό κόμβο ως τον προηγούμενο του νέου
		length++; //αύξησε το μέγεθος της λίστας κατά 1
	}

	//Συνάρτηση που διαγράφει τον τελευταίο κόμβο της λίστας
	void Delete() {
		try {
			if (!end) { //αν η λίστα είναι άδεια, εμφάνισε μήνυμα λάθους και τερμάτισε το πρόγραμμα
				throw 0;
			}
			if (end->GetPrevious()) { //Εέαν ο τελευταίος κόμβος έχει προηγούμενο, δηλαδή η λίστα περιέχει τουλάχιστον 2 στοιχεία
				Node<T>* newEnd = end->GetPrevious(); //αποθήκευσε τη διεύθυνση του προηγούμενου του τελευταίου
				delete end; //διέγραψε τον τελευταίο
				end = newEnd; //θέσε τον προηγούμενό του ως τον τελευταίο
				end->SetNext(NULL); //θέσε το δείκτη επόμενου του νέου τελευταίου ως NULL
			}
			else { //αν η λίστα έχει μόνο ένα αντικείμενο
				delete start; //διέγραψε τον πρώτο
				delete end; //διέγραψε τον τελευταίο
			}
			length--; //μείωσε το μήκος της λίστας κατά 1
		}
		catch (int e) {
			std::cout << "Error: List is empty.\n";
			std::exit(1);
		}
	}

	//Συνάρτηση που διαγράφει έναν κόμβο της λίστας με βάση ένα δείκτη της θέσης του στη λίστα. Λαμβάνει ως παράμετρο το δείκτη θέσης
	void Delete(int index) {
		try {
			if (index >= length) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			else if (index == length - 1) { //αν ο δείκτης αντιστοιχεί στον τελευταίο κόμβο
				Delete(); //κάλεσε τη συνάρτηση αφαίρεσης του τελευταίου
			}
			else if (index == 0){ //αν ο δείκτης αντιστοιχεί δτον πρώτο κόμβο
				Node<T>* newStart = start->GetNext(); //αποθήκευσε τη διεύθυνση του επόμενου του πρώτου κόμβου
				if (newStart) //αν υπάρχει, δηλαδή αν η λίστα έχει πάνω από ένα στοιχείο
					newStart->SetPrevious(NULL); //τότε θέσε τον προηγούμενο του κόμβου αυτού ως NULL
				delete start; //διέγραψε τον πρώτο
				start = newStart; //θέσε τον επόμενο ως τον πρώτο
				length--; //μείωσε το μέγεθος της λίστας κατά 1
			}
			else { //σε οποιαδήποτε άλλη περίπτωση
				int i;
				Node<T>* currentNode; //τρέχον κόμβος
				//διαδικασία αναζήτησης
				if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
					i = 0; //θέσε το i 0
					currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
					while (i < index) { //όσο το i είναι μικρότερο του δείκτη
						currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
						i++; //αύξησε το i κατά 1
					}
				}
				else { //αλλιώς
					i = length - 1; //θέσε το i μήκος λίστας - 1
					currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
					while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
						currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
						i--; //μείωσε το i κατά 1
					}
				}
				Node<T>* next = currentNode->GetNext(); //αποθήκευσε τη διεύθυνση του επόμενου του τρέχοντος κόμβου
				Node<T>* previous = currentNode->GetPrevious(); //αποθήκευσε τη διεύθυνση του προηγούμενου του τρέχοντος κόμβου
				next->SetPrevious(previous); //θέσε ως τον προηγούμενο του επόμενου τον προηγούμενο του τρέχοντος
				previous->SetNext(next); //θέσε ως τον επόμενο του προηγούμενου τον επόμενο του τρέχοντος
				delete currentNode; //διέγραψε τον τρέχον κόμβο
				length--; //μείωσε το μέγεθος της λίστας κατά 1
			}
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			std::exit(1);
		}
	}

	 //Συνάρτηση που διαγράφει έναν κόμβο με βάση τη διεύθυνσή του στη μνήμη. Δέχεται ως παράμετρο τη διεύθυνση του κόμβου.
	void Delete(Node<T>* node) {
		Node<T>* previous = node->GetPrevious(); //Αποθήκευσε τον προηγούμενο του προς διαγραφή κόμβου
		Node<T>* next = node->GetNext(); //Αποθήκευσε τον επόμενο του προς διαγραφή κόμβου
		delete node; //Δέγραψε τον κόμβο
		if (previous) //Αν ο προηγούμενος υπάρχει, δηλαδή ο κόμβος δε διαγράφεται από την αρχή της λίστας
			previous->SetNext(next); //Θέσε ως επόμενό του τον επόμενο του διεγραμμένου κόμβου
		if(next) //Αν ο επόμενος υπάρχει, δηλαδή ο κόμβος δε διαγράφεται από το τέλος της λίστας
			next->SetPrevious(previous); //Θέσε ως προηγούμενό του τον προηγούμενο του διεγραμμένου κόμβου
		length--; //μείωσε το μέγεθος της λίστας κατά 1
	}

	//Συνάρτηση ανάκτησης δεδομένων ενός κόμβου. Λαμβάνει ως όρισμα τη θέση του κόμβου του οποίου τα δεδομένα θέλουμε να ανακτήσουμε.
	T GetData(int index) {
		try {
			if (index >= length || index < 0) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			int i;
			Node<T>* currentNode; //τρέχον κόμβος
			//διαδικασία αναζήτησης
			if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
				i = 0; //θέσε το i 0
				currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
				while (i < index) { //όσο το i είναι μικρότερο του δείκτη
					currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
					i++; //αύξησε το i κατά 1
				}
			}
			else { //αλλιώς
				i = length - 1; //θέσε το i μήκος λίστας - 1
				currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
				while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
					currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
					i--; //μείωσε το i κατά 1
				}
			}
			return currentNode->GetData(); //επέστρεψε τα δεδομένα του τρέχοντος κόμβου
		}
		catch(int e){
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//Συνάρτηση ανάκτησης της διεύθυνσης των δεδομένων ενός κόμβου. Λαμβάνει ως όρισμα τη θέση του κόμβου του οποίου τα δεδομένα θέλουμε να ανακτήσουμε.
	T* GetDataRef(int index) {
		try {
			if (index >= length || index < 0) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			int i;
			Node<T>* currentNode; //τρέχον κόμβος
			//διαδικασία αναζήτησης
			if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
				i = 0; //θέσε το i 0
				currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
				while (i < index) { //όσο το i είναι μικρότερο του δείκτη
					currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
					i++; //αύξησε το i κατά 1
				}
			}
			else { //αλλιώς
				i = length - 1; //θέσε το i μήκος λίστας - 1
				currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
				while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
					currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
					i--; //μείωσε το i κατά 1
				}
			}
			return &currentNode->GetData(); //επέστρεψε τη διεύθυνση των δεδομένων του τρέχοντος κόμβου
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//Συνάρτηση ανάκτησης κόμβου με βάση τη θέση του στη λίστα. Λαμβάνει ως όρισμα τη θέση του κόμβου.
	Node<T>* GetNode(int index) {
		try {
			if (index >= length || index < 0) { //Αν ο δείκτης είναι εκτός των ορίων της λίστας
				throw 0; //Τότε εμφανίσε μήνυμα λάθους και τερμάτισε το πρόγραμμα
			}
			int i;
			Node<T>* currentNode; //τρέχον κόμβος
			//διαδικασία αναζήτησης
			if (index <= length / 2) { //αν ο δείκτης εισόδου είναι στη μέση η πριν τη μέση της λίστας
				i = 0; //θέσε το i 0
				currentNode = start; //θέσε τον πρώτο κόμβο ως τον τρέχον κόμβο
				while (i < index) { //όσο το i είναι μικρότερο του δείκτη
					currentNode = currentNode->GetNext(); //θέσε στον τρέχον κόμβο τον επόμενό του
					i++; //αύξησε το i κατά 1
				}
			}
			else { //αλλιώς
				i = length - 1; //θέσε το i μήκος λίστας - 1
				currentNode = end; //θέσε τον τελευταίο κόμβο ως τον τρέχον κόμβο
				while (i > index) { //όσο το i είναι μεγαλύτερο του δείκτη
					currentNode = currentNode->GetPrevious(); //θέσε στον τρέχον κόμβο τον προηγούμενό του
					i--; //μείωσε το i κατά 1
				}
			}
			return currentNode; //επέστρεψε τη διεύθυνση του κόμβου
		}
		catch (int e) {
			std::cout << "Error: Index out of bounds.\n";
			exit(1);
		}
	}

	//Συνάρτηση που επιστρέφει το μέγεθος της λίστας
	int Length() {
		return length;
	}
};

//Συνάρτηση που παράγει έναν τυχαίο ακέραιο αριθμό στο κλειστό διάστημα των τιμών των παραμέτρων της.
int RandomInt(int lowerBound, int upperBound) {
	std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_int_distribution<> randomInt(lowerBound, upperBound);
	return randomInt(re);
}

//Συνάρτηση που παράγει έναν τυχαίο αριθμό κινητής υποδιαστωλής στο κλειστό διάστημα των τιμών των παραμέτρων της.
double RandomDouble(double lowerBound, double upperBound) {
	std::default_random_engine re{ static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
	std::uniform_real_distribution<double> randomDouble(lowerBound, upperBound + 0.0001);
	return randomDouble(re);
}

//Κλάση που αναπαριστά τους χρήστες της εφαρμογής.
class User {
private:
	DoublyLinkedList<GPSSignal> trajectory = DoublyLinkedList<GPSSignal>(); //τροχιά χρήστη
	DoublyLinkedList<Node<GPSSignal>*> dayStart = DoublyLinkedList<Node<GPSSignal>*>(); //λίστα με δείκτες προς του πρώτους κόμβους κάθε μέρας
	Location location = Location::GenerateRandomLocation(0, 1000, 0, 1000); //τρέχουσα θέση χρήστη
	Location target = location; //τρέχον προορισμός χρήστη
	double speedms = 0.0; //ταχύτητα χρήστη σε m/s
	double speedY = 0.0; //συνιστώσα ταχύτητας χρήστη στον άξονα y
	double speedX = 0.0; //συνιστώσα ταχύτητας χρήστη στον άξονα x
	bool moving = false; //μεταβλητή που δείχνει αν κινείται ο χρήστης
	bool waiting = false; //μεταβλητή που δείχνει αν περιμένει ο χρήστης
	double waitingTime = 0.0; //χρόνος που θα περιμένει ο χρήστης
	double startWaitingTime = 0.0; //χρονική στιγμή έναρξης αναμονής
	int direction = 0; //κατεύθυνση διανύσματος κίνησης χρήστη
	bool infected = false; //κατάσταση μόλυνσης χρήστη
	bool reached = false; //μεταβλητή που δείχνει αν ο χρήστης έχει φτάσει στον προορισμό του
	bool signal = true; //μεταβλητή που δείχνει αν το GPS του χρήστη έχει σήμα
	double* currentTime = NULL; //δείκτης προς το ρολόι του προγράμματος
	double signalDownTime = 0.0; //χρόνος για τον οποίο θα χαθεί το σήμα του GPS του χρήστη
	double signalDownStartTime = 0.0; //χρονική στιγμή που ξεκινά η έλλειψη σήματος
	bool nextStart = false; //μεταβλητή που δείχνει αν ο επόμενος κόμβος της τροχιάς του χρήστη θα είναι ο πρώτος μιας μέρσς

public:
	//deafult constructor
	User() {

	}

	//constructor που δέχεται ως ορίσματα την κατάσταση της μόλυνσης του χρήστη και τη διεύθυνση του ρολογιού του πεογράμματος
	User(bool infected, double* currentTime) {
		this->infected = infected;
		this->currentTime = currentTime;
	}

	//Συνάρτηση που προσομοιώνει τη συμπεριφορά του χρήστη
	void Simulate() {
		if (signal && RandomInt(0, 9) < 2 ) { //αν το GPS έχει σήμα, αποφάσισε αν το σήμα θα χαθεί με πιθανότητα απώλειας 20%
			signalDownTime = RandomInt(0, 10) * 30.0; //επέλεξε τυχαία τη διάρκεια της απώλειας
			signalDownStartTime = *currentTime; //θέσε την τρέχουσα χρονική στιγμή του προγράμματος ως τη χρονική στιγμή εκκίνισης της απώλειας
			signal = false; //θέσε το σήμα false
		}
		else if (!signal && *currentTime - signalDownStartTime >= signalDownTime) { //αν το GPS δεν έχει σήμα και έχει περάσει η διάρκεια απώλειας
			signal = true; //θέσε το σήμα true
		}

		if (moving) { //εάν ο χρήστης κινείται
			location.SetLat(location.GetLat() + speedY * 30.0); //μετέβαλε τη θέση του στον άξονα y κατα την ταχύτητά του στον άξονα y επί 30
			location.SetLon(location.GetLon() + speedX * 30.0); //μετέβαλε τη θέση του στον άξονα x κατα την ταχύτητά του στον άξονα x επί 30
			if (!Location::HasReachedTarget(location, target, direction)) { //εάν ο χρήστης έχει φτάσει στον προορισμό του
				location = target; //θέσε τη θέση του προορισμού του ως την τρέχουσα θέση του
				moving = false; //θέσε την κίνηση σε false
			}
		}
		else { //αν δεν κινείται
			if (!waiting) { //αν δεν περιμένει
				waitingTime = RandomInt(0, 120) * 30.0; //τότε επέλεξε μια τυχαία διάρκεια αναμονής
				if (waitingTime > 0.0) { //αν η διάρκεια είναι μεγαλύτερη του 0
					startWaitingTime = *currentTime; //θέσε την τρέχουσα ώρα προγράμματος ως τη χρονική στιγμή έναρξης της αναμονής
					waiting = true; //θέσε την αναμονή true
				}
			}
			else if (*currentTime - startWaitingTime >= waitingTime) { //αν ο χρήστης περιμένει και έχει περάσει ο χρόνος αναμονής
				waiting = false; //θέσε την αναμονή false
			}

			if (!waiting) { //αν ο χρήστης δεν περιμένει
				do {
					target = Location::GenerateRandomLocation(0, 1000, 0, 1000); //επέλεξε έναν τυχαίο προορισμό
				} while (location.GetLat() == target.GetLat() && location.GetLon() == target.GetLon()); //διαφορετικού της τρέχουσας τοποθεσίας
				speedms = RandomDouble(3.0, 6.0) * 0.27778; //επέλεξε μια ταχύτητα από 3 εώς 6 km/h και μετέρεψέ τη σε m/s
				direction = Location::Direction(location, target); //βρες την κατεύθυνση του διανύσματος του χρήστη
				double dist = Location::LocationDifference(location, target); //βρες την απόσταση μεταξύ των δύο τοποθεσιών
				double time = dist / speedms; //βρες το χρόνο που θα κάνει ο χρήστης να φτάσει στον προορισμό του
				speedY = (target.GetLat() - location.GetLat()) / time; //βρες τη συνιστώσα της ταχύτητας στον άξονα y
				speedX = (target.GetLon() - location.GetLon()) / time; //βρες τη συνιστώσα της ταχύτητας στον άξονα x
				moving = true; //θέσε την κίνηση σε true
			}
		}

		if (!signal && *currentTime - (int)(*currentTime * (1 / 86400.0)) * 86400.0 == 0){ //αν δεν υπάρχει σήμα και η τρέχουσα χρονική στιγμή του προγράμματος αντιστοιχεί στην αρχή μιας μέρας
			nextStart = true; //ο επόμενος κόμβος θα είναι ο πρώτος της μέρας
		}

		if (signal) { //αν υπάρχει σήμα
			trajectory.Insert(GPSSignal(location, *currentTime)); //η τρέχουσα θέση του χρήστη μαζί με τη χρονική στιγμή εισάγωνται στην τροχιά
			if (*currentTime - (int)(*currentTime * (1 / 86400.0)) * 86400.0 == 0 || nextStart){ // αν η τρέχουσα χρονική στιγμή του προγράμματος αντιστοιχεί στην αρχή μιας μέρας ή ο επόμενος κόμβος είναι ο πρώτος μιας μέρας
				dayStart.Insert(trajectory.GetNode(trajectory.Length() - 1)); //βάλε τον κόμβο στη λίστα με τους πρώτους κόμβους κάθε μέρας
				SummarizeTrajectory(dayStart.Length() - 1, 2); //συνόψισε την προχθεσινή τροχιά
				if (*currentTime != 0) { //αν το πρόγραμμα δε βρίσκεται στην πρώτη χρονική στιγμή
					Repair(dayStart.Length() - 2); //επιδιόρθωσε τη χθεσιή τροχιά
				}
				nextStart = false; //ο επόμενος κόμβοε δε θα είναι ο πρώτος μιας μέρας
			}
		}

	}

	//συνάρτηση που επιστρέφει τη διεύθυνση της τροχιάς του χρήστη
	DoublyLinkedList<GPSSignal>* GetTrajectory() {
		return &trajectory;
	}

	//συνάρτηση που επιστρέφει τη διεύθυνση της λίστας με τους πρώτους κόμβους κάθε μέρας
	DoublyLinkedList<Node<GPSSignal>*>* GetDayStart() {
		return &dayStart;
	}

	//Συνάρτηση που θέτει την κατάσταση μόλυνσης του χρήστη
	void SetInfectionStatus(bool infected) {
		this->infected = infected;
	}

	//Συνάρτηση που ανακτά την κατάσταση μόλυνσης του χρήστη
	bool GetInfectionStatus() {
		return infected;
	}

	//Συνάρτηση που επιδιορθώνει την τροχιά μιας μέρας του χρήστη. Λαμβάνει ως παράμετρο τη μέρα.
	//Eπιδιορθώνει την τροχιά του χρήστη, προσπαθώντας να εκτιμήσει τις θέσεις του χρήστη σε περιόδους 
	//απώλειας σήματος και εισάγοντας τις εκτιμήσεις αυτές στην τροχιά του. 
	void Repair(int day) {
		Node<Node<GPSSignal>*>* utilNode = dayStart.GetNode(day); //Αποθήκευσε τον κόμβο που περιέχει τον πρώτο κόμβο της μέρας
		Node<GPSSignal>* startNode = utilNode->GetData(); //Αποθήκευσε τον πρώτο κόμβο της μέρας. Σε κάθε έλεγχο μεταξύ 2 κόμβων, αυτός ο δείκτης θα περιέχει τον κόμβο έναρξης.
		Node<GPSSignal>* endNode; //Σε κάθε έλεγχο μεταξύ 2 κόμβων, αυτός ο δείκτης θα περιέχει τον κόμβο λήξης.
		Node<GPSSignal>* nextDayNode; //Ο πρώτος κόμβος της επόμενης μέρες
		double startNodeTime; //χρονική στιγμή κόμβου αρχής
		double endNodeTime; //χρονική στιγμή κόμβου τέλους
		Location startNodeLoc; //τοποθεσία κόμβου αρχής
		Location endNodeLoc; //τοποθεσία κόμβου τέλους
		double xspeed; //ταχύτητα στον άξονα y
		double yspeed; //ταχύτητα στον άξονα x
		double timedif; //χρονική διαφορά μεταξύ 2 κόμβων
		if (utilNode->GetNext()) { //εάν υπάρχει επόμενος πρώτος κόμβος μέρας
			nextDayNode = utilNode->GetNext()->GetData(); //αποθήκευσέ τον
		}
		else {
			nextDayNode = NULL;
		}
		endNode = startNode->GetNext(); //θέσε τον επόμενο του κόμβου αρχής ως τον κόμβο  λήξης
		while (endNode != nextDayNode) { //για κάθε κόμβο της τροχιάς της μέρας
			startNodeTime = startNode->GetData().GetTimestamp(); //αποθήκευσε τη χρονική στιγμή κόμβου αρχής
			endNodeTime = endNode->GetData().GetTimestamp(); //αποθήκευσε τη χρονική στιγμή κόμβου τέλους
			startNodeLoc = startNode->GetData().GetLocation(); //αποθήκευσε την τοποθεσία του κόμβου αρχής
			endNodeLoc = endNode->GetData().GetLocation(); //αποθήκευσε την τοποθεσία του κόμβου λήξης
			timedif = endNodeTime - startNodeTime; //υπολόγισε τη χρονική διαφορά των κόμβων
			if (timedif > 30) { //εάν η διαφορά είναι μεγαλύτερη των 30 δευτερολέπτων
				yspeed = (endNodeLoc.GetLat() - startNodeLoc.GetLat()) / timedif * 30; //υπολόγισε την ταχύτητα στον άξονα y
				xspeed = (endNodeLoc.GetLon() - startNodeLoc.GetLon()) / timedif * 30; //υπολόγισε την ταχύτητα στον άξονα x
				int nodesToInsert = timedif / 30 - 1; //υπολόγισε πόσοι κόμβοι πρέπει να εισαχθούν
				double newLocY = startNodeLoc.GetLat(); //θέση y νέου κόμβου
				double newLocX = startNodeLoc.GetLon(); //θέση x νέου κόμβου
				double newTime = startNodeTime; //χρονική στιγμή νέου κόμβου
				for (int i = 0; i < nodesToInsert; i++) { //για όσους κόμβους πρέπει να εισαχθούν
					//υπολόγισε τα δεδομένα του νέου κόμβου
					newLocY += yspeed;
					newLocX += xspeed;
					newTime += 30;
					trajectory.InsertBefore(endNode, GPSSignal(newLocY, newLocX, newTime)); //τοποθέτησε το νέο κόμβο πριν τον κόμβο λήξης
				}
			}
			startNode = endNode; //θέσε τον κόμβο τέλους ως τον κόμβο αρχής
			endNode = startNode->GetNext(); //θέσε τον επόμενο κόμβο ως κόμβο τέλους
		}
	}

	//Συνάρτηση που συνοψίζει την τροχιά μιας μέρας μερικές μέρες πριν μία άλλη.
	//Η συνάρτηση ξεκινά τον πρώτο κόμβο μας μέρας και διαγράφει από την τροχιά της 
	//μέρας όσους επόμενούς της κόμβους βρίσκονται μέσα σε μία ακτίνα, εώς ότου να βρει 
	//έναν κόμβο που βρίσκεται εκτός της ακτίνας, στην οποία περίπτωση επαναλαμβάνει την 
	//διαδικασία για τον κόμβο αυτό. 
	void SummarizeTrajectory(int day, int daysBefore) {
		if (day - daysBefore >= 0) { //αν η μέρα της οποίας την τροχιά θέλουμε να απλοποιήσουμε υπάρχει
			Node<Node<GPSSignal>*>* utilNode = dayStart.GetNode(day - daysBefore); //αποθήκευσε τον κόμβο που περιέχει τον πρώτο κόμβο της μέρας
			Node<GPSSignal>* centerNode = utilNode->GetData(); //αποθήκευσε τον πρώτο κόμβο της μέρας. αυτός ο δείκτης θα δείχνει στον κόμβο που βρίσκεται στο κέντρο της ακτίνας διαγραφής
			Location centerNodeLocation = centerNode->GetData().GetLocation(); //αποθήκευσε την τοποθεσία του κεντρικού κόμβου
			Node<GPSSignal>* nextDayNode = utilNode->GetNext() ? utilNode->GetNext()->GetData() : NULL; //αν υπάρχει αποθήκευσε τον πρώτο κόμβο της επόμενης μέρας
			Node<GPSSignal>* currentNode = centerNode->GetNext(); //θέσε τον επόμενο κόμβο του κεντρικού ως τον τρέχον κόμβο που εξετάζεται
			Location currentLocation; //τοποθεσία τρέχοντος κόμβου
			while (centerNode->GetNext() != nextDayNode && centerNode != nextDayNode) { //για κάθε κόμβο της μέρας
				currentLocation = currentNode->GetData().GetLocation(); //αποθήκευσε την τοποθεσία του τρέχοντος κόμβου
				if (Location::LocationDifference(centerNodeLocation, currentLocation) < 50) { //έαν ο τρέχον κόμβος απέχει λιγότερο από 50 μέτρα από τον κεντρικό
					trajectory.Delete(currentNode); //διέγραψέ τον
				}
				else { //αλλιώς
					centerNode = currentNode; //θέσε τον τρέχον κόμβο ως το νέο κεντρικό
					centerNodeLocation = currentLocation; //θέσε τη θέση του ως τη νέα κεντρική
				}
				currentNode = centerNode->GetNext(); //θέσε ως τρέχον κόμβο τον επόμενο
			}
		}
	}
};

struct Utility {
	//Συνάρτηση που εντοπίζει πιθανές μολύνσης συγκρίνοβτας τις τροχιές ενός χρήστη και των ασθενών.
	//Δέχεται ως παραμέτρους ένα χρήστη, μία μέρα για την οποία θέλουμε να γίνει ο έλεγχος και μία λίστα χρηστών
	static bool PossibleCOVID19Infection(User* user, int day, DoublyLinkedList<User>* patients) {
		Node<GPSSignal>* currentUserTrajectoryNode; //τρέχον κόμβος της τροχιάς του χρήστη
		Node<GPSSignal>* userNextDayStart = NULL; //πρώτος κόμβος επόμενης μέρας
		if (user->GetDayStart()->GetNode(day)->GetNext()) { // εάν υπάρχει, αποθήκευσε τον πρώτο κόμβο της επόμενης μέρας
			userNextDayStart = user->GetDayStart()->GetNode(day)->GetNext()->GetData();
		}
		Node<User>* currentPatientNode = patients->GetNode(0); //αποθήκευσε τον πρώτο χρήστη από τη λίστα. ο δείκτης αυτός θα κρατά τον ασθενή που συγκρίνουμε με το χρήστη
		Node<GPSSignal>* currentPatientTrajectoryNode; //τροχιά τρέχοντος ασθενή
		Node<GPSSignal>* currentPatientNextDayStart; //πρώτος κόμβος της επόμενης μέρας της τροχιάς του ασθενή
		Location currentPatientLocation; //τρέχουσα τοποθεσία ασθενή
		bool nearPatient = false; //μεταβλητή που δείχνει αν ο χρήστης βρίσκεται κοντα στον ασθενή
		bool breakOnNext = false; 
		double timeNearPatient = 0.0; //χρόνος που βρίσκεται κοντα στον ασθενή
		double currentPatientTime; //χρονική στιγμή τοποθεσίας ασθενή
		while (currentPatientNode) { //για κάθε χρήστη στη λίστα χρηστών
			if (currentPatientNode->GetData().GetInfectionStatus()) { //αν ο χρήστης είναι μολυσμένος
				currentPatientTrajectoryNode = currentPatientNode->GetData().GetDayStart()->GetData(day); //αποθήκευσε την αρχή της τροχιάς του ασθενή για τη μέρα
				currentPatientNextDayStart = NULL;
				if (currentPatientNode->GetData().GetDayStart()->GetNode(day)->GetNext()) { //αν υπάρχει, αποθήκευσε τον πρώτο κόμβο της επόμενης μέρας της τροχιάς του ασθενή
					currentPatientNextDayStart = currentPatientNode->GetData().GetDayStart()->GetNode(day)->GetNext()->GetData();
				}
				while (currentPatientTrajectoryNode != currentPatientNextDayStart) { //για κάθε κόμβο στην τροχιά του ασθενή για την ημέρα
					currentUserTrajectoryNode = user->GetDayStart()->GetData(day); //αποθήκευσε τον πρώτο κόμβο της ημέρας της τροχιάς του χρήστη
					currentPatientLocation = currentPatientTrajectoryNode->GetData().GetLocation(); //αποθήκευσε την τρέχουσα θέση του τρέχοντος ασθενή
					currentPatientTime = currentPatientTrajectoryNode->GetData().GetTimestamp(); //αποθήκευσε την τρέχουσα χρονική στιγμή του τρέχοντος ασθενή
					while (currentUserTrajectoryNode) { //για κάθε κόμβο της τροχιάς του χρήστη
						//αν ο χρήστης βρέθηκε το πολύ 2 ώρες μετά και το πολύ τρία μέτρα από την τρέχουσα τοποθεσία του ασθενή
						if (std::abs(currentPatientTime - currentUserTrajectoryNode->GetData().GetTimestamp()) <= 7200 && std::abs(Location::LocationDifference(currentPatientLocation, currentUserTrajectoryNode->GetData().GetLocation())) <= 3.0) {
							if (!nearPatient) { //τότε αν δε βρισκόταν κοντα στον ασθενή
								nearPatient = true; //τώρα βρίσκεται
							}
							else { //αλλιώς αν ήταν ήδη κοντα στον ασθενή
								//αύξησε το χρόνο που βρίσκεται κοντά στον ασθενή κατά τη χρονική διαφορά της τρέχουσας θέσης του με την προηγούμενη
								timeNearPatient += currentUserTrajectoryNode->GetData().GetTimestamp() - currentUserTrajectoryNode->GetPrevious()->GetData().GetTimestamp();
								if (timeNearPatient >= 1800) { //αν ο χρόνος είναι τουλάχιστον μισή ώρα
									return true; //τότε επέστρεψε true, καθώς ο χρήστης έχει πιθανώς μολυνθεί
								}
								if (currentUserTrajectoryNode == userNextDayStart) { //αν ο τρέχον κόμβος του χρήστη είναι ο πρώτος κόμβος της επόμενης μέρας
									breakOnNext = true; //διέκοψε τον έλεγχο για τον τρέχον ασθενή όταν ο χρήστης απομακρυνθεί από αυτόν
								}
							}
						}
						else { //αν δε βρίσκεται κοντα στον ασθενή
							if (breakOnNext) //διέκοψε τον έλεγχο για τον ασθενή αν χρειάζεται. με αυτό τον τρόπο ο έλεγχος μπορεί να συνεχίσει και στη επόμενη μέρα,αν ο χρήστης βρισκόταν κοντά στον ασθενή στο τέλος της προηγούμενης
								break;
							timeNearPatient = 0.0; //θέσε την ώρα κοντα στον ασθενή ως 0
							nearPatient = false; //ο χρήστης δε βρίσκεται κοντά στον ασθενή
						}
						currentUserTrajectoryNode = currentUserTrajectoryNode->GetNext(); //θέσε ο τρέχον κόμβο της τροχιάς του χρήστη τον επόμενο
					}
					currentPatientTrajectoryNode = currentPatientTrajectoryNode->GetNext(); //θέσε ως τρέχον κόμβο της τροχιάς του τρέχοντος ασθενή τον επόμενο
				}
			}
			currentPatientNode = currentPatientNode->GetNext(); //θέσε ως τρέχον ασθενή τον επόμενο
		}
		return false; //επέστρεψε false αν δε βρέθηκε κάποια πιθανή μόλυνση
	}

	//Συνάρτηση που βρίσκει πόσοι χρήστε βρίσκονταν σε μια περιοχή σε ένα χρονικό διάστημα μιας μέρας για τουλάχιστον κάποιο χρόνο.
	//Η συνάρτηση λαμβάνει ως παραμέτρους τη μέρα, ελάχιστες και μέγιστες συντεταγμένες και χρόνο, το ελάχιστο χρονικό διάστημα και μία λίστα χρηστών
	static int FindCrowdedPlaces(int day, double startTime, double endTime, double lowerBoundLat, double loweBoundLon, double upperBoundLat, double upperBoundLon, double minimumStayDuration, DoublyLinkedList<User>* users) {
		int usersInArea = 0; //πόσοι χρήστες βρέθηκαν στην περιοχή
		startTime += 86400.0 * day; //απόλυτη ελάχιστη χρονική στιγμή
		endTime += 86400.0 * day; //απόλυτη μέγιστη χρονική στιγμή
		Node<GPSSignal>* currentTrajectoryNode; //τρέχον κόμβος τροχιάς τρέχοντος χρήστη
		Node<GPSSignal>* nextDayNode; //πρώτος κόμβος επόμενης μέρας
		Node<Node<GPSSignal>*>* utilNode; //κόμβος που περιέχει τον πρώτο κόμβο της μέρας
		double currentLat; //τρέχον γεωγραφικό πλάτος
		double currentLon; //τρέχον γεωγραφικό μήκος
		double currentTimestamp; //τρέχουσα χρονική στιγμή
		Node<GPSSignal>* inAreaStartNode = NULL; //κόμβος τροχιάς που ο χρήστης εισήλθε στην περιοχή
		bool inArea = false; //μεταβλητή που δείχνει αν ο χρήστης βρίσκεται στη περιοχή

		for (int i = 0; i < users->Length(); i++) { //για κάθε χρήστη
			utilNode = users->GetNode(i)->GetData().GetDayStart()->GetNode(day); //αποθήκευσε τον κόμβο που περιέχει τον πρώτο κόμβο της μέρας
			currentTrajectoryNode = utilNode->GetData(); //αποθήκευσε τον πρώτο κόμβο της μέρας. αυτός ο κόμβος θα δείχνει τον τρέχον κόμβο της τροχιάς του χρήστη
			nextDayNode = utilNode->GetNext() ? utilNode->GetNext()->GetData() : NULL; //αποθήκευσε τον κόμβο της επόμενης μέρας, αν υπάρχει
			while (currentTrajectoryNode != nextDayNode) { //για κάθε κόμβο της τροχιάς του χρήστη
				currentLat = currentTrajectoryNode->GetData().GetLocation().GetLat(); //αποθήκευσε το γεωγραφικό πλάτος
				currentLon = currentTrajectoryNode->GetData().GetLocation().GetLon(); //αποθήκευσε το γεωγραφικό μήκος
				currentTimestamp = currentTrajectoryNode->GetData().GetTimestamp(); //αποθήκευσε τη χρονική στιγμή
				//αν η τρέχουσα θέση του χρήστη βρίσκεται στην περιοχή στο απαιτούμενο χρονικό διάστημα και υπάρχει επόμενος κόμβος
				if (currentTimestamp >= startTime && currentTimestamp <= endTime && currentLat >= lowerBoundLat && currentLat <= upperBoundLat && currentLon >= loweBoundLon && currentLon <= upperBoundLon && currentTrajectoryNode->GetNext() != nextDayNode) {
					if (!inArea) { //αν ο χρήστης δε βρίσκεται ήδη στη περιοχή
						inAreaStartNode = currentTrajectoryNode; //θέσε τον τρέχον κόμβο ως τον κόμβο εισόδου
						inArea = true; //ο χρήστης βρίσκεται στην περιοχή
					}
				}
				else { //αν η τρέχουσα τοποθεσία είναι εκτός περιοχής
					if (inArea) { //αν ο χρήστης βρίσκεται ήδη στην περιοχή
						inArea = false; //ο χρήστης δε βρίσκεται στην περιοχή
						//αν ο χρήστης παρέμεινε για τουλάχιστον τον ελάχιστο απαιτύμενο χρόνο στην περιοχή
						if (currentTrajectoryNode->GetPrevious()->GetData().GetTimestamp() - inAreaStartNode->GetData().GetTimestamp() >= minimumStayDuration) {
							usersInArea++; //αύξησε το πλήθος των χρηστών στην περιοχή κατά 1
							break; //προχώρα στον έλεγχο του επόμενου χρήστη
						}
					}
				}
				currentTrajectoryNode = currentTrajectoryNode->GetNext(); //θέσε τον επόμενο κόμβο της τροχιάς ως τον τρέχον
			}
		}

		return usersInArea; //επέστρεψε το πλήθος των χρηστών στην περιοχή
	}
};

//κύριο πρόγραμα
int main()
{
	double currentTime = 0.0; //ρολόι προγράμματος
	DoublyLinkedList<User> users = DoublyLinkedList<User>(); //λίστα χρηστών
	//εισαγωγή 12 χρηστών στη λίστα. οι δύο από αυτούς είναι μολυσμένοι
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

	Node<User>* userNodeToCheck; //κόμβος χρήστη για τον οποίο πρέπει να εκτελεστεί κάποια ενέργεια
	User* userToCheck; //χρήστης για τον οποίο πρέπει να εκτελεστεί κάποια ενέργεια
	bool yesNoControl = false; //input κατάφασης/άρνησης
	//inputs για την εκτέλεση της FindCrowdedPlaces από το διαχειριστή
	int lowerLatBound;
	int upperLatBound;
	int lowerLonBound;
	int upperLonBound;
	int lowerTimeBound;
	int upperTimeBound;
	int minimumStayDuration;

	//βρόγχος προγράμματος
	while (true) {
		for (int i = 0; i < users.Length(); i++) { //για κάθε χρήστη
			users.GetNode(i)->GetDataRef()->Simulate(); //προσομοίωσε τη συμπεριφορά του
		}
		if (currentTime != 0 && currentTime - (int)(currentTime * (1 / 86400.0)) * 86400.0 == 0) { //αν ο χρόνος προγράμματος δεν είναι μηδέν και αντιστοιχεί στην αρχή κάποιας μέρας
			userNodeToCheck = users.GetNode(0); //αποθήκευσε τον κόμβο του πρώτου χρήστη
			while (userNodeToCheck) { //για κάθε χρήστη
				userToCheck = userNodeToCheck->GetDataRef(); //αποθήκευσε το χρήση
				//αν δεν είναι μολυσμένος, έλεγξε αν πιθανώς μολύνθηκε μέσα στην προηγούμενη μέρα
				if (!userToCheck->GetInfectionStatus() && userToCheck->GetDayStart()->Length() - 2 >= 0 && Utility::PossibleCOVID19Infection(userToCheck, userToCheck->GetDayStart()->Length() - 2, &users)) {
					std::cout << "New possible infection\n"; //αν βρέθηκε πιθανή μόλυνση, εμφάνισε μήνυμα ειδοποίησης
					userToCheck->SetInfectionStatus(true); //και θέσε την κατάσταση μόλυνσής του σε true
				}
				userNodeToCheck = userNodeToCheck->GetNext(); //θέσε τον επόμενο χρήστη ως τρέχον
			}
			//Όταν η μέρα τελεώσει, ρώτα το χρήστη αν θέλει να δει αν κάποια περιοχή είχε πολύ κόσμο
			std::cout << "Day complete.\nWould you like to search for crowded areas?\nyes(1)	no(0)\n";
			std::cin >> yesNoControl;
			if (yesNoControl) {
				//μάζεψε της παραμέτρους της συνάρτησης από το χρήστη
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
				//εκτέλεσε τη FindCrowdedPlaces και εκτύπωσε το αποτέλεσμα
				std::cout << "\nUsers in area: " << Utility::FindCrowdedPlaces(users.GetData(0).GetDayStart()->Length() - 2, lowerTimeBound, upperTimeBound, lowerLatBound, lowerLonBound, upperLatBound, upperLonBound, minimumStayDuration, &users) << std::endl << std::endl;
			}
			//ρώτα το χρήστη αν θέλει να βγει από το πρόγραμα
			std::cout << "Exit program?\nyes(1)		no(0)\n";
			std::cin >> yesNoControl;
			if (yesNoControl) {
				break;
			}
		}
		currentTime += 30.0; //αύξησε το ρολόοι του χρήστη κατά 30
	}
} 
