#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Header.h"
#include "json.hpp"
#include <algorithm>
#include <cctype>
#include <limits>

using json = nlohmann::json;

json jusers, jreservations, jhotels, jstatistic, j_copy;

std::string::size_type size;
std::size_t digits;

std::string name, surname, password, again_password, username, Rcountry, years;
int code;
const int admincode = 1515;

std::string hotels[500];
std::string countrys[500];
std::string hotel, country;

int choise;
std::string wordchoise;

void loaduserfile() {
	std::ifstream usersFile("users.json");
	if (usersFile.is_open()) {
		usersFile >> jusers;
	}
}

void saveuserfile() {
	std::ofstream usersFile("users.json");
	usersFile << std::setw(4) << jusers << std::endl;
	usersFile.close();
}

void loadreservationfile() {
	std::ifstream reservationfile("reservations.json");
	if (reservationfile.is_open()) {
		reservationfile >> jreservations;
	}
}

void savereservationfile() {
	std::ofstream reservationfile("reservations.json");
	reservationfile << std::setw(4) << jreservations << std::endl;
	reservationfile.close();
}

void loadhotelsfile() {
	std::ifstream hotelsFile("hotels.json");
	if (hotelsFile.is_open()) {
		hotelsFile >> jhotels;
	}
}

void savehotelsfile() {
	std::ofstream hotelsFile("hotels.json");
	hotelsFile << std::setw(4) << jhotels << std::endl;
	hotelsFile.close();
}

void registration() {
	system("cls");

	loaduserfile();

	std::cout << "Administratora kods: ";
	std::cin >> code;
	do {
		std::cout << "Vards: ";
		std::getline(std::cin >> std::ws, name);
	} while (check_usrn_surn(name));
	do {
		std::cout << "Uzvards: ";
		std::getline(std::cin >> std::ws, surname);
	} while (check_usrn_surn(surname));
	do {
		std::cout << "Parole: ";
		std::getline(std::cin >> std::ws, password);
		std::cout << "Atkartota parole: ";
		std::getline(std::cin >> std::ws, again_password);
	} while (password != again_password);
		std::cout << "Username: ";
		std::getline(std::cin >> std::ws, username);
	do {
		std::cout << "Valsts: ";
		std::getline(std::cin >> std::ws, Rcountry);
	} while (checkfordigitsandsymbols(Rcountry));
	std::cout << "Gadi: ";
	std::getline(std::cin >> std::ws, years);
	
	jusers[username]["name"] = name;
	jusers[username]["surname"] = surname;
	jusers[username]["password"] = password;
	jusers[username]["username"] = username;
	jusers[username]["country"] = Rcountry;
	jusers[username]["years"] = years;

	if (code == admincode) {
		jusers[username]["admin"] = true;
	}
	else {
		jusers[username]["admin"] = false;
	}

	saveuserfile();
}

void login() {
	system("cls");

	loaduserfile();
	
	std::cout << "Lietotajvardu: ";
	std::getline(std::cin >> std::ws, username);
	std::cout << "Parole: ";
	std::getline(std::cin >> std::ws, password);

	if (password == jusers[username]["password"]) {
		if (jusers[username]["admin"] == true) {
			adminMain();
		}
		else {
			userMain();
		}
	}
	else {
		main();
	}
}

int main() {
	system("cls");

	std::cout << "Sveicinats Viesnicas sistema\n";
	std::cout << "[1]Registreties\n";
	std::cout << "[2]Ielogoties sistema\n";
	std::cout << "[0]Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> choise;

	if (choise == 1) {
		registration();
		main();
	}
	else if (choise == 2) {
		login();
		main();
	}
	else if (choise == 0) {
		return 0;
	}
	else {
		std::cin.clear();
		std::cin.ignore(); 
		main();
	}
}

struct Date
{
	int d, m, y;
};

const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };

int countLeapYears(Date d)
{
	int years = d.y;

	if (d.m <= 2)
		years--;

	return years / 4 - years / 100 + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
	long int n1 = dt1.y * 365 + dt1.d;

	for (int i = 0; i < dt1.m - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);

	long int n2 = dt2.y * 365 + dt2.d;
	for (int i = 0; i < dt2.m - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1);
}

int payforroom(std::string sakums, std::string beigas, int cenaparnr) {
	int summa;

	int day1, day2;
	int month1, month2;
	int year1, year2;

	int daystogether;

	day1 = std::stoi(beigas.substr(0, 2), &size);
	day2 = std::stoi(sakums.substr(0, 2), &size);
	month1 = std::stoi(beigas.substr(3, 2), &size);
	month2 = std::stoi(sakums.substr(3, 2), &size);
	year1 = std::stoi(beigas.substr(6, 4), &size);
	year2 = std::stoi(sakums.substr(6, 4), &size);

	Date sakumsdate = { day2, month2, year2 };
	Date beigasdate = { day1, month1, year1 };

	daystogether = getDifference(sakumsdate, beigasdate);

	summa = daystogether * cenaparnr;

	return summa;
}

bool isDate(std::string date1, std::string date2) {
	std::string::size_type sz;

	int day1;
	int day2;
	int month1;
	int month2;
	int year1;
	int year2;


	if (checkfordigitsandsymbols(date1) && checkfordigitsandsymbols(date2)) {
		day1 = std::stoi(date1.substr(0, 2), &sz);
		day2 = std::stoi(date2.substr(0, 2), &sz);
		month1 = std::stoi(date1.substr(3, 2), &sz);
		month2 = std::stoi(date2.substr(3, 2), &sz);
		year1 = std::stoi(date1.substr(6, 4), &sz);
		year2 = std::stoi(date2.substr(6, 4), &sz);
	}


	if (date1[2] == '-' && date1[5] == '-' && date2[2] == '-' && date2[5] == '-') {
		if (day1 >= 1 && day1 <= 31 && day2 >= 1 && day2 <= 31) {
			if (month1 >= 1 && month1 <= 12 && month2 >= 1 && month2 <= 12) {
				if (year1 >= 2019 && year1 <= 2030 && year2 >= 2019 && year2 <= 2030) {
					return true;
				}
			}
		}
	}
	return false;
}

bool isDateInRange(int day, int month, int year, int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear) {
	int entryDate = (year * 10000) + (month * 100) + day;
	int startDate = (startYear * 10000) + (startMonth * 100) + startDay;
	int endDate = (endYear * 10000) + (endMonth * 100) + endDay;

	if (entryDate >= startDate && entryDate <= endDate) {
		return true;
	}
	else {
		return false;
	}
}

void reserveroom() {
	std::string roomprice, room;
	std::string reservationdatestart, reservationdateend;

	std::string reservationnumber;
	std::string shortcut, stars;
	std::string nameandsurname;

	int roompriceinteger, price, nr;

	bool wrong = false, datecorrect = false;

	loadhotelsfile();
	loadreservationfile();
	loaduserfile();

	system("cls");

	std::cout << "Viesnica " << hotel << "\n";
	std::cout << "Vai gribat rezervet numurinu viesnica?[1-JA, 0-NE]";
	std::cin >> wordchoise;

	if (wordchoise == "1") {
		system("cls");
		do {
			std::cout << "Datums kura velaties rezervet numurinu[31-11-2019]: ";
			std::getline(std::cin >> std::ws, reservationdatestart);
			std::cout << "Datums lidz kuram velaties rezervet numurinu[31-11-2019]: ";
			std::getline(std::cin >> std::ws, reservationdateend);
			if (isDate(reservationdatestart, reservationdateend)) {	datecorrect = false;}
			else { datecorrect = true;}
		} while (datecorrect);

		system("cls");
		for (auto& el : jhotels.at(country).at("hotels").at(hotel).at("hotel-rooms").items()) {
			std::string num = el.key();
			if (jhotels.at(country).at("hotels").at(hotel).at("hotel-rooms").at(num).at("reserved") == false) {
				room = el.key();
			}
		}

		roompriceinteger = jhotels.at(country).at("hotels").at(hotel).at("hotel-room-price");

		price = payforroom(reservationdatestart, reservationdateend, roompriceinteger);

		std::cout << "KOPA: " << price << "Eiro\n";
		system("pause");

		name = jusers.at(username).at("name");
		surname = jusers.at(username).at("surname");
		shortcut = jhotels.at(country).at("shortcut");
		stars = jhotels.at(country).at("hotels").at(hotel).at("hotel-stars");
		nameandsurname = name + "-" + surname;

		nr = rand() % 100000 + 1;
		reservationnumber = std::to_string(nr);

		do {
			nr = rand() % 100000 + 1;
			reservationnumber = std::to_string(nr);
			if (jreservations.count(nameandsurname) != 0) {
				for (auto& el : jreservations.at(nameandsurname).at("reservations").items()) {
					std::string item = el.key();
					int itemINT = std::stoi(item, &size);
					if (itemINT == nr) {wrong = true;}
					else {wrong = false;}
				}
			}
		} while (wrong);

		jreservations[nameandsurname]["reservations"][reservationnumber]["country"] = country;
		jreservations[nameandsurname]["reservations"][reservationnumber]["shortcut"] = shortcut;
		jreservations[nameandsurname]["reservations"][reservationnumber]["room"] = room;
		jreservations[nameandsurname]["reservations"][reservationnumber]["hotel"] = hotel;
		jreservations[nameandsurname]["reservations"][reservationnumber]["stars"] = stars;
		jreservations[nameandsurname]["reservations"][reservationnumber]["reservation-number"] = reservationnumber;
		jreservations[nameandsurname]["reservations"][reservationnumber]["date-start"] = reservationdatestart;
		jreservations[nameandsurname]["reservations"][reservationnumber]["date-end"] = reservationdateend;
		jreservations[nameandsurname]["reservations"][reservationnumber]["price"] = price;

		jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved"] = true;
		jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved-until"] = reservationdatestart;
		jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved-from"] = reservationdateend;

		savereservationfile();
		savehotelsfile();
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
}

void searchroombycountry() {
	std::string search, searchresults[250];

	int i = 1, res = 0;

	system("cls");

	std::cout << "Valsts nosaukums: ";
	std::cin >> search;

	loadhotelsfile();

	for (auto& el : jhotels.items()) {
		std::string searchres = el.key();
		res = isSubstring(search, searchres);

		if (res != -1) {
			std::cout << i << "." << searchres << "\n";
			searchresults[i - 1] = searchres;
			i++;
		}
	}

	if (i > 1) {
		std::cout << "[0]atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> choise;

		if (choise == 0) {
			return;
		}
		else if (choise != i && choise >= 1) {
			i = 1;
			system("cls");
			std::cout << "Izvelieties viesnicu:\n";
			if (jhotels.empty() == false) {
				for (auto& el : jhotels.at(searchresults[choise - 1]).at("hotels").items()) {
					std::cout << i << "." << el.key() << "\n";
					hotels[i - 1] = el.key();
					i++;
				}
			}
			std::cout << "[0]atpakal\n";
			std::cout << "Izvele: ";
			std::cin >> choise;

			if (choise == 0) {
				return;
			}
			else if (choise > 0 && choise < i) {
				country = searchresults[choise - 1];
				hotel = hotels[choise - 1];
				reserveroom();
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				searchroombycountry();
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			searchroombycountry();
		}
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "\nNav rezultati!\n";
		system("pause");
	}
}

void searchroombyhotel() {
	system("pause");
}

void searchroombystars() {
	std::string search, searchResults[250];

	int i = 1, res = 0;

	system("cls");

	std::cout << "Viesnicas zvaigznes: ";
	std::cin >> search;

	loadhotelsfile();

	for (auto& el : jhotels.items()) {
		std::string c = el.key();
		for (auto& gl : jhotels.at(c).at("hotels").items()) {
			std::string v = gl.key();
			if (search == jhotels.at(c).at("hotels").at(v).at("hotel-stars")) {
				std::cout << i << "." << v << "\n";
				searchResults[i - 1] = v;
				countrys[i - 1] = c;
				i++;
			}
		}
	}

	if (i > 1) {
		std::cout << "[0]atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> choise;

		if (choise == 0) {
			return;
		}
		else if (choise != i && choise >= 1) {
			country = countrys[choise - 1];
			hotel = searchResults[choise - 1];
			reserveroom();
			return;
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	else
	{
		std::cout << "\nNav rezultats!\n";
		system("pause");
	}
}

void searchroombyfreedate() {
	std::string search, searchResults[250];

	int i = 1, res = 0;

	system("cls");

	bool p = false;

	loadhotelsfile();

	do {
		std::cout << "Datums kura velaties rezervet viesnicu[31-01-2019]: ";
		std::cin >> search;
		if (isDate(search, search)){p = false;}
		else {p = true;}
	} while (p);


	for (auto& el : jhotels.items()) {
		std::string c = el.key();
		for (auto& gl : jhotels.at(c).at("hotels").items()) {
			std::string v = gl.key();
			for (auto& cl : jhotels.at(c).at("hotels").at(v).at("hotel-rooms").items()) {
				std::string n = cl.key();

				if (jhotels.at(c).at("hotels").at(v).at("hotels-rooms").at(n).at("reserved") == false) {
					std::cout << i << "." << v << "\n";
					searchResults[i - 1] = v;
					countrys[i - 1] = c;
					i++;
				}
			}
		}
	}

	if (i > 1) {
		std::cout << "[0]atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> choise;

		if (choise == 0) {
			return;
		}
		else if (choise != i && choise >= 1) {
			country = countrys[choise - 1];
			hotel = searchResults[choise - 1];
			reserveroom();
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

	}
	else
	{
		std::cout << "res:" << res << "\nNav rezultats!\n";
		system("pause");
	}
}

void searchroom() {
	system("cls");

	std::cout << "Meklet pec\n";
	std::cout << "[1]valsts\n";
	std::cout << "[2]viesnicas\n";
	std::cout << "[3]zvaigznem\n";
	std::cout << "[4]briviem datumiem\n";
	std::cout << "[0]atpakal\n";
	std::cout << "Izvele:";
	std::cin >> choise;

	if (choise == 1) {
		searchroombycountry(); 
	}
	else if (choise == 2) {
		searchroombyhotel(); 
	}
	else if (choise == 3) {
		searchroombystars(); 
	}
	else if (choise == 4) {
		searchroombyfreedate(); 
	}
	else if (choise == 0) {
		return;
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	searchroom();
}

void editreservation(std::string vuu, std::string reznr, std::string numurins) {
	int roomprice;
	std::string startdate, enddate, newstartdate, newenddate;
	bool p = false;

	loadhotelsfile();
	loadreservationfile();

	system("cls");

	std::cout << "Jaunais sakuma datums: ";
	std::cin >> newstartdate;

	std::cout << "Jaunais beigu datums: ";
	std::cin >> newenddate;


	jreservations[vuu]["reservations"][reznr]["date-end"] = newenddate;
	jhotels[country]["hotels"][hotel]["hotel-rooms"][numurins]["reserved-until"] = newenddate;
	jreservations[vuu]["reservations"][reznr]["date-start"] = newstartdate;
	jhotels[country]["hotels"][hotel]["hotel-rooms"][numurins]["reserved-from"] = newstartdate;

	savehotelsfile();
	savereservationfile();
}

void printreservation(std::string reservationnum) {
	std::string nameandsurname, shortcut, startdate, enddate, room, stars;

	nameandsurname = name + "-" + surname;

	loadreservationfile();

	system("cls");

	country = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("country");
	shortcut = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("shortcut");
	hotel = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("hotel");
	startdate = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("date-start");
	enddate = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("date-end");
	room = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("room");
	stars = jreservations.at(nameandsurname).at("reservations").at(reservationnum).at("stars");

	std::ofstream HTML("Rezervacija.html");

	HTML << "<!DOCTYPE html><html><head><style>table, th, td{border: 1px solid black;}</style></head><body><table>" <<
		"<tr><th>" << name << " " << surname << "</th><th>" << "Rez. Nr. " << reservationnum << "</th></tr>" <<
		"<tr><th>" << "Valsts" << "</th><th>" << country << " (" << shortcut << ")" << "</th></tr>" <<
		"<tr><th>" << "Viesnica" << "</th><th>" << hotel << "</th></tr>" <<
		"<tr><th>" << "Sakums" << "</th><th>" << startdate << "</th></tr>" <<
		"<tr><th>" << "Beigas" << "</th><th>" << enddate << "</th></tr>" <<
		"<tr><th>" << "Numurins" << "</th><th>" << room << "</th></tr>" <<
		"<tr><th>" << "Zvaigznes" << "</th><th>" << stars << "</th></tr>" <<
		"</table></body></html>";
	HTML.close();
}

void reservation() {
	std::string nameandsurname, room;

	std::string reservations[250], reservationss;

	bool nepareizi = false;
	bool exists = false;

	loadhotelsfile();
	loadreservationfile();
	loaduserfile();

	name = jusers.at(username).at("name");
	surname = jusers.at(username).at("surname");

	nameandsurname = name + "-" + surname;

	system("cls");
	std::cout << "Rezervacijas:\n\n";

	int i = 1;
	if (jreservations.empty() == false) {
		if (jreservations.count(nameandsurname) != 0) {
			for (auto& l : jreservations.at(nameandsurname).at("reservations").items()) {
				std::cout << i << "." << l.key() << "\n";
				reservations[i - 1] = l.key();
				i++;
			}
		}
	}

	std::cout << "[0]Atpakal\n\n";
	std::cout << "Izvele:";
	std::cin >> choise;

	reservationss = reservations[choise - 1];

	if (choise == 0) {
		return;
	}
	else if (choise > 0 && choise < i) {

		country = jreservations.at(nameandsurname).at("reservations").at(reservations[choise - 1]).at("country");
		hotel = jreservations.at(nameandsurname).at("reservations").at(reservations[choise - 1]).at("hotel");
		room = jreservations.at(nameandsurname).at("reservations").at(reservations[choise - 1]).at("room");
		do {
			system("cls");
			std::cout << "[1]Labot datumus\n";
			std::cout << "[2]Atcelt rezervaciju\n";
			std::cout << "[3]Drukat rezervaciju\n";
			std::cout << "[0]Atpakal\n\n";
			std::cout << "Izvele:";
			std::cin >> choise;

			if (choise == 1) {
				editreservation(nameandsurname, reservationss, room);
			}
			else if (choise == 2) {
				jreservations.at(nameandsurname).at("reservations").erase(reservationss);

				if (jhotels[country]["hotels"][hotel]["hotel-rooms"].count(room) != 0) {

					jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved"] = false;
					jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved-until"] = "";
					jhotels[country]["hotels"][hotel]["hotel-rooms"][room]["reserved-from"] = "";
				}

				savereservationfile();
				savehotelsfile();

				return;
			}
			else if (choise == 3) {
				printreservation(reservationss);
				nepareizi = true;
			}
			else if (choise == 4) {
				return;
			}
			else {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				nepareizi = true;
			}
			nepareizi = true;
		} while (nepareizi);
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		reservation();
	}
}

void userMain() {
	system("cls");

	std::cout << "Sveicinats lietotaj\n" << std::endl;
	std::cout << "[1]Meklet/rezervet numurinu\n";
	std::cout << "[2]Rezervacijas\n";
	std::cout << "[0]Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> choise;

	if (choise == 0) {
		return;
	}
	else if (choise == 1) {
		searchroom(); 
		userMain();
	}
	else if (choise == 2) {
		reservation(); 
		userMain();
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		userMain();
	}
}

void addcountry() {
	std::string countryname, shortcut, hotelname, stars, maxrooms;

	int maxhotels, roomprice;

	bool wrong = false;

	system("cls");

	loadhotelsfile();

	do {
		std::cout << "Valsts nosaukums - ";
		std::getline(std::cin >> std::ws, countryname);
		std::transform(countryname.begin(), countryname.end(), countryname.begin(), ::tolower);
	} while (checkfordigitsandsymbols(countryname));

	do {
		std::cout << "Valsts saisinajums - ";
		std::getline(std::cin >> std::ws, shortcut);
	} while (checkfordigitsandsymbols(shortcut));

	do {
		std::cout << "Viesnicu skaits - ";
		std::cin >> maxhotels;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			wrong = true;
		}
		else {
			wrong = false;
		}
	} while (wrong);

	for (int x = 1; x <= maxhotels; x++) {
		do {
			std::cout << "Viesnicas nosaukums - ";
			std::getline(std::cin >> std::ws, hotelname);
			std::transform(hotelname.begin(), hotelname.end(), hotelname.begin(), ::tolower);
		} while (checkfordigitsandsymbols(hotelname));

		do {
			std::cout << "Viesnicas zvaigznu skaits - ";
			std::cin >> stars;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				wrong = true;
			}
			else if (stars.find_first_not_of("0123456789") == std::string::npos) {
				if (std::stoi(stars, &size) < 1 || std::stoi(stars, &size) > 5) {
					wrong = true;
				}
				else {
					wrong = false;
				}
			}
			else {
				wrong = true;
			}
		} while (wrong);

		do {
			std::cout << "Numurinu skaits viesnica - ";
			std::cin >> maxrooms;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				wrong = true;
			}
			else if (maxrooms.find_first_not_of("0123456789") == std::string::npos) {
				if (std::stoi(maxrooms, &size) < 1 || std::stoi(maxrooms, &size) > 500) {
					wrong = true;
				}
				else {
					wrong = false;
				}
			}
			else {
				wrong = true;
			}
		} while (wrong);

		do {
			std::cout << "Cena par numurinu - ";
			std::cin >> roomprice;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
				wrong = true;
			}
			else if (roomprice > 0 && roomprice <= 99999) {
				wrong = false;
			}
			else {
				wrong = true;
			}
		} while (wrong);

		jhotels[countryname]["shortcut"] = shortcut;
		jhotels[countryname]["Max-hotels"] = maxhotels;
		jhotels[countryname]["hotels"][hotelname]["hotel-name"] = hotelname;
		jhotels[countryname]["hotels"][hotelname]["hotel-stars"] = stars;
		jhotels[countryname]["hotels"][hotelname]["hotel-room-price"] = roomprice;
		jhotels[countryname]["hotels"][hotelname]["max-hotel-rooms"] = maxrooms;

		for (int x = 1; x <= std::stoi(maxrooms, &size); x++) {
			std::string room = std::to_string(x);
			jhotels[countryname]["hotels"][hotelname]["hotel-rooms"][room]["reserved"] = false;
			jhotels[countryname]["hotels"][hotelname]["hotel-rooms"][room]["reserved-from"] = "";
			jhotels[countryname]["hotels"][hotelname]["hotel-rooms"][room]["reserved-until"] = "";
		}
	}
	
	savehotelsfile();

	system("pause");
}

void change_key(json &jj, std::string& labojamais, std::string& labojums)
{
	auto itr = jj.find(labojamais);
	std::swap(jj[labojums], itr.value());
	jj.erase(itr);
}

void change_key_addon(std::string labojamais, std::string nosaukums)
{
	loadhotelsfile();

	change_key(jhotels, labojamais, nosaukums);

	savehotelsfile();
}

void editcountry() {
	bool wrong = false;

	int i, choice2;

	std::string newcountryname, newshortcut, newhotelname, newstars, newrooms;
	int newmaxhotels, newroomprice;

	std::string countryname, shortcut, hotelname, stars, maxrooms;
	int maxhotels, roomprice;

	loadhotelsfile();

	do {
		system("cls");

		int x = 0;
		if (jhotels.empty() == false) {
			for (auto& el : jhotels.items()) {
				std::cout << x + 1 << "." << el.key() << std::endl;
				countrys[x] = el.key();
				x++;
			}
		}

		std::cout << "[0]Atpakal\n";
		std::cout << "Izvele: ";
		std::cin >> choise;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			wrong = true;
		}
		else if (choise > 0 && choise < x + 1) {
			wrong = false;
		}
		else if (choise == 0) {
			adminMain();
		}
		else {
			wrong = true;
		}
	} while (wrong);

	std::string labojamais = countrys[choise - 1];

	do {
		system("cls");
		std::cout << "[1]Labot valsts nosaukumu\n";
		std::cout << "[2]Labot valsts saisinajumu\n";
		std::cout << "[3]Labot viesnicu skaitu valsti\n";
		std::cout << "[4]Labot viesnicu nosaukumus\n";
		std::cout << "[5]Labot viesnicu zvaigznu skaitu\n";
		std::cout << "[6]Labot numurina cenu\n";
		std::cout << "[0]Iziet\n\n";
		std::cout << "Izvele: ";
		std::cin >> choise;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			wrong = true;
		}
		else if (choise > 0 && choise < 8) {
			wrong = false;
		}
		else if (choise == 0) {
			editcountry();
		}
		else {
			wrong = true;
		}
	} while (wrong);

	loadhotelsfile();

	if (choise == 1) {
		system("cls");
		std::cout << "Jaunais valsts nosaukums - ";
		std::cin >> newcountryname;
		std::transform(newcountryname.begin(), newcountryname.end(), newcountryname.begin(), ::tolower);
		change_key_addon(labojamais, newcountryname);
		adminMain();
	}
	else if (choise == 2) {
		std::cout << "Jauns valsts saisinajums -  ";
		std::cin >> newshortcut;
		jhotels[labojamais]["shortcut"] = newshortcut;
		savehotelsfile();
	}
	else if (choise == 3) {
		int vs = jhotels.at(labojamais).at("Max-hotels");
		do {
			std::cout << "Jaunais viesnicu skaits - ";
			std::cin >> newmaxhotels;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else {
				wrong = false;
			}
		} while (wrong);

		jhotels[labojamais]["Max-hotels"] = newmaxhotels;

		savehotelsfile();

		i = 0;
		for (auto& el : jhotels.at(labojamais).at("hotels").items()) {
			hotels[i] = el.key();
			i++;
		}

		if (newmaxhotels < vs) {
			for (int j = vs; j > newmaxhotels; j--) {
				jhotels.at(labojamais).at("hotels").erase(hotels[j - 1]);
			}
		}
		else {
			for (int j = vs; j < newmaxhotels; j++) {
				system("cls");
				do {
					std::cout << "Viesnicas nosaukumu -";
					std::getline(std::cin >> std::ws, hotelname);
					std::transform(hotelname.begin(), hotelname.end(), hotelname.begin(), ::tolower);
				} while (checkfordigitsandsymbols(hotelname));

				do {
					std::cout << "Viesnicas zvaigznu skaitu -";
					std::cin >> stars;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						wrong = true;
					}
					else {
						wrong = false;
					}
				} while (wrong);

				do {
					std::cout << "Cenu par numurinu - ";
					std::cin >> newroomprice;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						wrong = true;
					}
					else {
						wrong = false;
					}
				} while (wrong);

				do {
					std::cout << "Numurinu skaits - ";
					std::cin >> newrooms;
					if (std::cin.fail()) {
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						wrong = true;
					}
					else {
						wrong = false;
					}
				} while (wrong);

				jhotels[labojamais]["hotels"][hotelname]["hotel-name"] = hotelname;
				jhotels[labojamais]["hotels"][hotelname]["hotel-stars"] = stars;
				jhotels[labojamais]["hotels"][hotelname]["hotel-room-price"] = newroomprice;
				jhotels[labojamais]["hotels"][hotelname]["hotel-rooms"] = newrooms;
				jhotels[labojamais]["Max-hotels"] = newmaxhotels;

				savehotelsfile();
			}
		}
		savehotelsfile();
	}
	else if (choise == 4) {
		do {
			int i = 0;

			system("cls");

			std::cout << "Izvelieties viesnicu: " << std::endl;
			if (jhotels[labojamais].count("hotels") != 0) {
				for (auto& el : jhotels.at(labojamais).at("hotels").items()) {
					std::cout << i + 1 << "." << el.key() << "\n";
					hotels[i] = el.key();
					i++;
				}
			}

			std::cout << "[0]atpakal\n\n";
			std::cout << "Izvele: ";
			std::cin >> choice2;


			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (choice2 > 0 && choice2 < i + 1) {
				wrong = false;
			}
			else if (choice2 == 0) {
				editcountry();
			}
			else {
				wrong = true;
			}
		} while (wrong);

		hotelname = hotels[choice2 - 1];

		system("cls");

		std::cout << "Jaunais nosaukums: ";
		std::getline(std::cin >> std::ws, newhotelname);
		std::transform(newhotelname.begin(), newhotelname.end(), newhotelname.begin(), ::tolower);

		j_copy = jhotels.at(labojamais).at("hotels").at(hotelname);
		jhotels.at(labojamais).at("hotels").erase(hotelname);
		jhotels[labojamais]["hotels"][newhotelname] = j_copy;
		j_copy.clear();

		savehotelsfile();
	}
	else if (choise == 5) {
		do {
			system("cls");
			int i = 0;

			for (auto& el : jhotels.at(labojamais).at("hotels").items()) {
				std::cout << i + 1 << "." << el.key() << "\n";
				hotels[i] = el.key();
				i++;
			}

			std::cout << "[0]atpakal\n";
			std::cout << "Izvele: ";
			std::cin >> choice2;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (choice2 > 0 && choice2 < i + 1) {
				wrong = false;
			}
			else if (choice2 == 0) {
				editcountry();
			}
			else {
				wrong = true;
			}

		} while (wrong);

		system("pause");

		stars = jhotels.at(labojamais).at("hotels").at(hotels[choice2 - 1]).at("hotel-stars");

		do {
			system("cls");
			std::cout << "Zvaigznu skaits: ";
			std::cin >> newstars;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (newstars.find_first_not_of("0123456789") == std::string::npos) {
				if (std::stoi(newstars, &size) < 1 || std::stoi(newstars, &size) > 5) {
					wrong = true;
				}
				else {
					wrong = false;
				}
			}
			else {
				wrong = true;
			}

		} while (wrong);

		jhotels[labojamais]["hotels"][hotels[choice2 - 1]]["hotel-stars"] = newstars;

		savehotelsfile();

	}
	else if (choise == 6) {
		do {
			int i = 0;
			if (jhotels[labojamais].count("hotels") != 0) {
				for (auto& el : jhotels.at(labojamais).at("hotels").items()) {
					std::cout << i + 1 << "." << el.key() << "\n";
					hotels[i] = el.key();
					i++;
				}
			}

			std::cout << "[0]atpakal\n";
			std::cout << "Izvele: ";
			std::cin >> choice2;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (choice2 > 0 && choice2 < i + 1) {
				wrong = false;
			}
			else if (choice2 == 0) {
				editcountry();
			}
			else {
				wrong = true;
			}
		} while (wrong);

		system("pause");

		roomprice = jhotels.at(labojamais).at("hotels").at(hotels[choice2 - 1]).at("hotel-room-price");

		do {
			system("cls");

			std::cout << "Jauna cena par numurinu: ";
			std::cin >> newroomprice;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else {
				wrong = false;
			}
		} while (wrong);

		jhotels[labojamais]["hotels"][hotels[choice2 - 1]]["hotel-room-price"] = newroomprice;

		savehotelsfile();
	}
	else if (choise == 8) {
		return;
	}
	else {
		adminMain();
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	system("pause");
}

void deletecountry() {
	int choice2, choice3;

	bool wrong = false;

	loadhotelsfile();

	system("cls");
	std::cout << "[1]Dzest valsti vai viesnicu\n";
	std::cout << "[0]Atpakal\n\n";
	std::cout << "Izvele: ";
	std::cin >> choise;

	if (choise == 1) {
		do {
			int h = 0;
			system("cls");
			for (auto& el : jhotels.items()) {
				std::cout << h + 1 << "." << el.key() << "\n";
				countrys[h] = el.key();
				h++;
			}
			std::cout << "[0]Atpakal\n";
			std::cout << "izvele: ";
			std::cin >> choice2;

			if (choice2 == 0) {
				deletecountry();
			}
			else if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (choice2 > 0 && choice2 <= h) {
				wrong = false;
			}
			else {
				wrong = true;
			}
		} while (wrong);

		do {
			system("cls");

			std::cout << "[1]Dzest viesnicu\n";
			std::cout << "[2]Dzest valsti\n";
			std::cout << "[0]Atpakal\n";
			std::cout << "Izvele: ";
			std::cin >> choice3;

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				wrong = true;
			}
			else if (choice3 > 0 && choice3 <= 3) {
				wrong = false;
			}
			else {
				wrong = true;
			}

		} while (wrong);

		if (choice3 == 1) {
			do {
				int g = 0;
				system("cls");
				if (jhotels[countrys[choise - 1]].count("hotels") != 0) {
					for (auto& el : jhotels.at(countrys[choice2 - 1]).at("hotels").items()) {
						std::cout << g + 1 << "." << el.key() << "\n";
						hotels[g] = el.key();
						g++;
					}
				}
				std::cout << "[0]Atpakal\n";
				std::cout << "Viesnica: ";
				std::cin >> choice3;

				if (choice3 == 0) {
					deletecountry();
				}
				else if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					wrong = true;
				}
				else if (choice3 > 0 && choice3 < g + 1) {
					jhotels.at(countrys[choice2 - 1]).at("hotels").erase(hotels[choice3 - 1]);
					savehotelsfile();
					wrong = true;
				}
				else {
					wrong = true;
				}
			} while (wrong);
		}
		else if (choice3 == 2) {
			jhotels.erase(countrys[choice2 - 1]);
			savehotelsfile();
		}
		else if (choice3 == 0) {
			deletecountry();
		}
	}
	else if (choise == 0) {
		adminMain();
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		deletecountry();
	}
}

void stat() {
	system("pause");
}

void adminMain() {
	system("cls");

	loadhotelsfile();

	std::cout << "Sveicinats, administrator\n";
	std::cout << "[1]Pievienot valsti\n";
	std::cout << "[2]Labot valsti\n";
	std::cout << "[3]Dzest valsti\n";
	std::cout << "[4]Statistika\n";
	std::cout << "[0]Iziet\n";
	std::cout << "Izvele: ";
	std::cin >> choise;

	if (choise == 1) {
		addcountry();
		adminMain();
	}
	else if (choise == 2) {
		editcountry();
		adminMain();
	}
	else if (choise == 3) {
		deletecountry();
		adminMain();
	}
	else if (choise == 4) {
		stat();
		adminMain();
	}
	else if (choise == 0) {
		return;
	}
	else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		adminMain();
	}
}