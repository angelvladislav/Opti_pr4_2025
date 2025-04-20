 /*
 *  GRAFO.CPP - Plantilla para la implementaci�n de la clase GRAFOS
 *
 *
 *               Autores : Angel Vladislav Alonso Yemelyantseva
 *               Correo : alu0101489827
 *               Cursos  : 2024-25
 */

 #include "grafo.h"

 void GRAFO :: destroy()
 {
     for (unsigned i=0; i< n; i++)
     {
         LS[i].clear();
         if (dirigido == 1)
                LP[i].clear();
     }
     LS.clear();
     if (dirigido == 1)
         LP.clear();
 
 }
 
 void GRAFO :: build (char nombrefichero[85], int &errorapertura)
 {
     ElementoLista     dummy;
     ifstream textfile;
     textfile.open(nombrefichero);
     if (textfile.is_open())
     {
         unsigned i, j, k;
         // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
         textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
         // los nodos internamente se numeran desde 0 a n-1
         // creamos las n listas de sucesores
         LS.resize(n);
         // leemos los m arcos
         for (k=0;k<m;k++)
             {
             textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
             //restamos 1 a los indices para quitar problemas de acceso a memoria
             i--;
             j--;
             //damos los valores a dummy.j y dummy.c
             dummy.j = j;
             //situamos en la posici�n del nodo i a dummy mediante push_back
             LS[i].push_back(dummy);
             //pendiente de hacer un segundo push_back si es no dirigido. O no.
             if (!dirigido){
                dummy.j = i;
                LS[j].push_back(dummy);
             }
         }
             //pendiente la construcci�n de LP, si es dirigido
             if (dirigido){
                ListaPredecesores();
             }
             //pendiente del valor a devolver en errorapertura
         errorapertura = 0;
     } else  {
         errorapertura = 1;
     }
 }
 
 GRAFO::~GRAFO()
 {
     destroy();
 }
 
 GRAFO::GRAFO(char nombrefichero[85], int &errorapertura)
 {
     build (nombrefichero, errorapertura);
 }
 
 void GRAFO:: actualizar (char nombrefichero[85], int &errorapertura)
 {
     //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
     destroy();
     //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
     build(nombrefichero, errorapertura);
 }
 
 unsigned GRAFO::Es_dirigido()
 {
    return dirigido;
 }
 
 void GRAFO::Info_Grafo()
 {
    if (dirigido){
        std::cout << "Este grado es DIRIGIDO" << std::endl;
        std::cout << "Tiene " << n << " nodos" << std::endl;
        std::cout << "Tiene " << m << " arcos" << std::endl;
    } else {
        std::cout << "Este grado es NO-DIRIGIDO" << std::endl;
        std::cout << "Tiene " << n << " nodos" << std::endl;
        std::cout << "Tiene " << m << " arcos" << std::endl; 
    }
 }
 
 void Mostrar_Lista(vector<LA_nodo> L)
 {
	for (unsigned i = 0; i < L.size(); i++) {
		std::cout << "Nodo " << i + 1 << ":";
		for (unsigned j = 0; j < L[i].size(); j++) {
			std::cout << " (" << L[i][j].j + 1 << ", " << L[i][j].c << ")";
		}
		std::cout << std::endl;
	}
 }

 void GRAFO :: Mostrar_Listas (int l)
 {
	if (l == 1){
		Mostrar_Lista(LS);
	} else if (l == -1){
		Mostrar_Lista(LP);
	}	else {
		Mostrar_Lista(LS);
	}
 }
 
 void GRAFO :: ListaPredecesores() //Recorre la lista de sucesores LS para construir la de predecesores, LP
 {
    LP.resize(n); 
    for (unsigned i=0;i<n;i++){
        for (unsigned j=0;j<LS[i].size();j++){
            ElementoLista dummy;
            dummy.j = i;
            dummy.c = LS[i][j].c;
            LP[LS[i][j].j].push_back(dummy);
        }
    }
 }
 
 void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes Conexas
 {
    visitado[i] = true; //visitamos el nodo i+1
    cout << i+1;
    for (unsigned j=0;j<LS[i].size();j++) { //recorremos la adyacencia del    nodo visitado, esto es, i+1
        if (!visitado[LS[i][j].j]) {
        cout << " , ";
        dfs_cc(LS[i][j].j, visitado);
        }
    }
 }
 
 void GRAFO::ComponentesConexas()
 {
    unsigned i, componentesconexas = 0;
    vector<bool> visitado;
    visitado.resize(n,false);
    for (unsigned i = 0; i < n; i++) {
        if (visitado[i] == false) {
            componentesconexas++;
            cout << "Componente Conexa " << componentesconexas << " : {";
            dfs_cc(i, visitado);
            cout << "}" << endl;
        }
    }
 }
 
 ////////////////////////////////////////////////////////////////////////////

 void GRAFO::ComponentesConexasDirigido()
 {
    unsigned i, componentesconexas = 0;
    vector<bool> visitado;
    visitado.resize(n,false);
    for (unsigned i = 0; i < n; i++) {
        if (visitado[i] == false) {
            componentesconexas++;
            cout << "Componente Conexa " << componentesconexas << " : {";
            dfs_cc_dirigido(i, visitado);
            cout << "}" << endl;
        }
    }
 }


 void GRAFO::dfs_cc_dirigido(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes Conexas
 {
    visitado[i] = true; //visitamos el nodo i+1
    cout << i+1;
    for (unsigned j=0;j<LS[i].size();j++) { //recorremos la adyacencia del    nodo visitado, esto es, i+1
        if (!visitado[LS[i][j].j]) {
        cout << " , ";
        dfs_cc_dirigido(LS[i][j].j, visitado);
        }
    }
    for (unsigned j=0;j<LP[i].size();j++) {
        if (!visitado[LP[i][j].j]) {
        cout << " , ";
        dfs_cc_dirigido(LP[i][j].j, visitado);
        }
    }
 }

 ////////////////////////////////////////////////////////////////////////////

 void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes fuertemente Conexas
 {
    visitado[i] = true; 
    cout << i+1;
    for (unsigned j=0;j<LP[i].size();j++) { 
        if (!visitado[LP[i][j].j]) {
        cout << " , ";
        dfs_cfc(LP[i][j].j, visitado);
        }
    }
 }
 
 void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind) //Este recorrido esta� hecho adhoc para calcular el orden postnumeraci�n de los nodos
 {
    visitado[i] = true;
    for (unsigned j = 0; j < LS[i].size(); j++) {
        if (!visitado[LS[i][j].j]) { 
            dfs_postnum(LS[i][j].j, visitado, postnum, postnum_ind);
        }
    }
    postnum[postnum_ind--] = i; 
 }
 
 void GRAFO::ComponentesFuertementeConexas()
 {
     unsigned postnum_ind, componentesfuertementeconexas = 0;
     vector<bool> visitado;
     vector<unsigned> postnum;
     visitado.resize(n, false);
     postnum.resize(n, UERROR);
     postnum_ind = n-1;

     for (unsigned i = 0; i < n; i++) {
         if (visitado[i] == false) {
             dfs_postnum(i, visitado, postnum, postnum_ind);
         }
     }

     visitado.clear();
     visitado.resize(n, false);
     for (unsigned i = 0; i < n; i++) {
         if (visitado[postnum[i]] == false) {
             componentesfuertementeconexas++;
             cout << "Componente Fuertemente Conexa " << componentesfuertementeconexas << " : {";
             dfs_cfc(postnum[i], visitado);
             cout << "}" << endl;
         }
     }
 }
 
 void GRAFO::Sollin() {
    vector<unsigned> Raiz(n);              // Raíz de cada nodo
    vector<vector<unsigned>> N(n);         // Componentes conexas
    unsigned pesoTotal = 0;                // Peso total del árbol

    // Inicialización
    for (unsigned i = 0; i < n; i++) {
        Raiz[i] = i;
        N[i].push_back(i);
    }

    unsigned AristasAdd = 0;

    while (AristasAdd < n - 1) {
        bool huboUnion = false;

        // Mostrar componentes al inicio
        cout << "\nComponentes al inicio de la iteración:\n";
        for (unsigned k = 0; k < n; k++) {
            if (!N[k].empty()) {
                cout << "Componente " << k << ": ";
                for (unsigned i = 0; i < N[k].size(); i++) {
                    cout << N[k][i] + 1 << " ";
                }
                cout << endl;
            }
        }

        for (unsigned k = 0; k < n; k++) {
            if (!N[k].empty()) {
                unsigned mink = maxint;
                unsigned ik = UERROR, jk = UERROR;

                for (unsigned idx = 0; idx < N[k].size(); idx++) {
                    unsigned u = N[k][idx];
                    for (unsigned j = 0; j < LS[u].size(); j++) {
                        unsigned v = LS[u][j].j;
                        unsigned coste = LS[u][j].c;

                        if (Raiz[u] != Raiz[v] && coste < mink) {
                            mink = coste;
                            ik = u;
                            jk = v;
                        }
                    }
                }

                if (ik != UERROR && jk != UERROR) {
                    cout << "Arista (" << ik + 1 << "," << jk + 1 << ") con peso " << mink << " añadida al árbol\n";
                    pesoTotal += mink;
                    AristasAdd++;
                    huboUnion = true;

                    unsigned raiz_ik = Raiz[ik];
                    unsigned raiz_jk = Raiz[jk];

                    unsigned NewRaiz, OldRaiz;
                    if (raiz_ik < raiz_jk) {
                        NewRaiz = raiz_ik;
                        OldRaiz = raiz_jk;
                    } else {
                        NewRaiz = raiz_jk;
                        OldRaiz = raiz_ik;
                    }

                    for (unsigned i = 0; i < N[OldRaiz].size(); i++) {
                        unsigned nodo = N[OldRaiz][i];
                        Raiz[nodo] = NewRaiz;
                        N[NewRaiz].push_back(nodo);
                    }

                    N[OldRaiz].clear();
                }
            }
        }

        // Mostrar componentes al final
        cout << "\nComponentes al final de la iteración:\n";
        for (unsigned k = 0; k < n; k++) {
            if (!N[k].empty()) {
                cout << "Componente " << k << ": ";
                for (unsigned i = 0; i < N[k].size(); i++) {
                    cout << N[k][i] + 1 << " ";
                }
                cout << endl;
            }
        }

        if (!huboUnion) break;
    }

    cout << "\n==========================\n";
    if (AristasAdd == n - 1) {
        cout << "El peso/coste del árbol es: " << pesoTotal << endl;
    } else {
        cout << "El grafo no es conexo\n";
    }
 }
