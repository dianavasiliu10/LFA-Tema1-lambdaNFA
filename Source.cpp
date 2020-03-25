#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("input.txt");

vector<vector<vector<int>>> G;
vector<char> alfabet;
vector<int> stFin;
vector<int> noduri;
vector<vector<int>> litere;
string cuv;


int getPos(char chr, vector<char> alf)
{
	for (int i = 0; i < alf.size(); i++)
		if (alf[i] == chr)
			return i;
	return -1;
}

bool isFin(int a)
{
    for (int i=0; i<stFin.size(); i++)
        if (stFin[i] == a)
            return true;
    return false;
}

int OK=0;

void DFS(int nod, int posLit)
{
    int poz=getPos(cuv[posLit],alfabet);
    int x;
    if (posLit<cuv.size())
    {
        if (G[nod][poz].size() != 0) // daca exista tranzitia cu litera curenta din cuvant
        {
            for (int i=0; i<G[nod][poz].size() && OK==0; i++)
            {
                x=G[nod][poz][i];
                DFS(x,posLit+1);
            }
        }
        if (G[nod][alfabet.size()-1].size() != 0) // daca exista tranzitia cu lambda
            for (int i=0; i<G[nod][alfabet.size()-1].size() && OK==0; i++)
            {
                x=G[nod][alfabet.size()-1][i];
                DFS(x,posLit);  // ia toate tranzitiile cu lambda, dar nu schimba litera
            }

    }
    else
    {
        if (isFin(nod))
        {
            cout<<"TRUE\n";
            OK=1;
        }
    }

}

int main()
{
	char chr;
    int n,m,q0,k,x,st,fn;
    fin >> n >> m;
	for (int i = 0; i < m; i++)
    {
        fin >> chr;
		alfabet.push_back(chr);			// citire alfabet
        litere.push_back(noduri);
    }

    alfabet.push_back('$');
    litere.push_back(noduri);

    for (int i=0; i<n; i++)
    {
        G.push_back(litere);
        /// G[i] = nodul de inceput = vector de vector
        /// G[i][j] = lista de vecini ai lui i pentru litera j = vector
        /// G[i][j][x] = nodul vecin al lui i mergand prin litera j = int
    }


	fin >> q0 >> k;
	for (int i = 0; i < k; i++)
    {
        fin >> x;
		stFin.push_back(x);			// citire stari finale
    }

	fin >> m;
	for (int i=1; i<=m; i++)
    {
        fin>>st>>chr>>fn;
        int valchr = getPos(chr,alfabet);
        G[st][valchr].push_back(fn);
    }


    fin>>n;
    for (int i=0; i<n; i++)
    {
        OK=0;
        fin>>cuv;
        cout<<cuv<<" - ";
        DFS(q0,0);
        if (OK==0)
            cout<<"FALSE\n";

    }

    return 0;

}
