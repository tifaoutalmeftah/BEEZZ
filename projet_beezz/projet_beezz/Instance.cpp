#include "Instance.h"

Instance::Instance(string file_name) :nb_parametres(), nb_criteres(), nb_options_par_parametre(), valeur_parametre_option_critere(), souhait_critere(), prix_max(), duree_de_vie_minimale(), seuil_ecolo(0.5)
{
	lire_instance_a_partir_dun_fichier_csv(file_name);
}

Instance::~Instance()
{
}

void Instance::lire_instance_a_partir_dun_fichier_csv(string file_name)
{
    valeur_parametre_option_critere = creation_matrice_donnees(file_name);
}

vector<string> split(string str, string token) {
    vector<string>result;
    while (str.size()) {
        double index = str.find(token);
        if (index != string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.size() == 0)result.push_back(str);
        }
        else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

vector<vector<vector<double> > > creation_matrice_donnees(string file_name) {
    ifstream file(file_name);
    int parametre = 1, option = 3;
    string cell;
    vector<string> ligne;
    vector<vector<vector<double> > > tab;
    getline(file, cell);
    getline(file, cell);
    ligne = split(cell, ",");

    while (ligne[3] != "") {

        if (ligne[1] != "") {
            vector<vector<double> > vect_of_vect;
            tab.push_back(vect_of_vect);
        }
        vector<double> vect_of_double;
        tab.back().push_back(vect_of_double);
        for (int i = 1; i < 7; i++) {
            double value;
            istringstream iss(ligne[option + i]);
            iss >> value;
            tab.back().back().push_back(value);
        }
        for (int i = 8; i < 11; i++) {
            double value;
            istringstream iss(ligne[option + i]);
            iss >> value;
            tab.back().back().push_back(value);
        }

        getline(file, cell);
        ligne = split(cell, ",");
    }

    return tab;
}


int Instance::get_nb_options_of_parametre(int i)
{
	if (i < 0 || i >= nb_parametres)
		throw invalid_argument("Attention!!!");
	return nb_options_par_parametre[i];
}

double Instance::get_note_parametre_option_critere(int i, int j, int c)
{
	if (i < 0 || i >= nb_parametres ||
		j < 0 || j >= get_nb_options_of_parametre(i) ||
		c < 0 || c >= nb_criteres)
		throw invalid_argument("Attention!!!");
	return valeur_parametre_option_critere[i][j][c];
}

double Instance::get_prix_parametre_option(int i, int j)
{
	if (i < 0 || i >= nb_parametres ||
		j < 0 || j >= get_nb_options_of_parametre(i))
		throw invalid_argument("Attention!!!");
	return valeur_parametre_option_critere[i][j][6];
}

double Instance::get_facteur_parametre_option(int i, int j)
{
	if (i < 0 || i >= nb_parametres ||
		j < 0 || j >= get_nb_options_of_parametre(i))
		throw invalid_argument("Attention!!!");
	return valeur_parametre_option_critere[i][j][7];
}

double Instance::get_duree_de_vie_parametre_option(int i, int j)
{
	if (i < 0 || i >= nb_parametres ||
		j < 0 || j >= get_nb_options_of_parametre(i))
		throw invalid_argument("Attention!!!");
	return valeur_parametre_option_critere[i][j][8];
}

int Instance::get_souhait_client_pour_critere(int c)
{

	if (c < 0 || c >= nb_criteres)
		throw invalid_argument("Attention!!!");
	return souhait_critere[c];
}

int Instance::get_nb_parametres()
{
	return nb_parametres;
}

int Instance::get_nb_criteres()
{
	return nb_criteres;
}

int Instance::get_nb_prix_max()
{
	return prix_max;
}

int Instance::get_duree_de_vie_minimale()
{
	return duree_de_vie_minimale;
}
