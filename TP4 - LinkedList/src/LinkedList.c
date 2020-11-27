#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this = NULL;

	this = (LinkedList*) malloc (sizeof(LinkedList));
	// Construyo el espacio de memoria que me va almacenar los datos
	// de la cabecera.

	if(this != NULL)
	{
		this->pFirstNode = NULL; // Que no apunte nada.
		this->size = 0; // Inicializo en cero.
	}
	return this; // Devuelvo la direccion de memoria de la cabecera.
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL)
	{
		returnAux = this->size; // Devuelvo el size/tamaño de la lista.
	}

	return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	//int len = ll_len(this);

	// Por que i < nodeIndex y no i <= nodeIndex?
	// No puedo saltar a NULL (por eso se hace desde uno antes).

	//              | Cabecera |  Nodo 0  |  Nodo 1  |  Nodo2  |
	// Direcciones: |  pNodo0  | pNodo 1  | pNodo 2  |   NULL  |
	// Saltos:      |    0     |     1    |     2    |    -    |

	// 1ra iteracion | 0 < 0 | No entra al for (no necesito saltar)
	// 2da iteracion | 0 < 1 | Entra en el for (salto 1 vez)
	// 3da iteracion | 0 < 2 | Entra en el for (salto 2 veces)

	if(this != NULL && nodeIndex >= 0 && nodeIndex < this->size)
	{
		pNode = this->pFirstNode; // Guardo la direccion de pNode 0
		// Si el indice es 0, devuelvo el valor que esta en la cabecera.

		// i NO es un indice de un array
		// Lo uso para contar las cantidad de veces que itero.
		for(int i = 0; i < nodeIndex; i++) // Itere nodeIndex veces
		{
			// i=1 pNode <- lo guardo (Direccion de pNode1). // Que ejecute 1 veces
			// i=2 pNode <- lo guardo (Direccion de pNode2). // Que ejecute 2 veces
			// i=n pNode <- lo guardo (Direccion de pNodeN). // Que ejecute N veces
			if(pNode != NULL)
			{
				pNode = pNode->pNextNode; // Puedo igualarlo por que es del tipo nodo.
			}
			// Cada vez que se ejecuta, avanzo un nodo.
		}
	}

	return pNode; // Devuelvo la direccion de memoria que yo quiera.
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
	return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
	int returnAux = -1;
	Node* pNode = NULL;
	Node* pPrevNode = NULL; // uso Nodo previo si nodeIndex > 0

	//&& pNode != NULL && pPrevNode != NULL

	// Si voy agregar en el ultimo
	// Si voy agregar en el primero (si esta vacia)
	// Si voy agregar en el medio

	if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
	{
		pNode = (Node*) malloc (sizeof(Node));

		if(pNode != NULL)
		{
			pNode->pElement = pElement; // Escribo/Inserto el elemento que me vino como argumento.

			if(nodeIndex == 0) // Agrego un nodo en la primer posicion
			{
				pNode->pNextNode = this->pFirstNode;
				this->pFirstNode = pNode;
				this->size++;
				returnAux = 0;
			}
			else // Agrego un nodo en el medio (entre 2 nodos) - si no es en el primero o ultimo, es en el medio.
			{
				// Version 2.0
				pPrevNode = getNode(this, (nodeIndex - 1)); // Que me traiga el ultimo nodo, traigo el anterior.
				pNode->pNextNode = pPrevNode->pNextNode;
				pPrevNode->pNextNode = pNode;
				this->size++;
				returnAux = 0;
			}

			/* Version 1.0
			else if(nodeIndex == this->size) // Agrego un nodo al final
			{
				pPrevNode = getNode(this, (nodeIndex - 1)); // Que me traiga el ultimo nodo, traigo el anterior.
				pPrevNode->pNextNode = pNode;
				pNode->pNextNode = NULL;
				this->size++;
				returnAux = 0;
			}
			else // Agrego un nodo en el medio (entre 2 nodos) - si no es en el primero o ultimo, es en el medio.
			{
				pPrevNode = getNode(this, (nodeIndex - 1)); // Que me traiga el ultimo nodo, traigo el anterior.
				pNode->pNextNode = pPrevNode->pNextNode;
				pPrevNode->pNextNode = pNode;
				this->size++;
				returnAux = 0;
			}*/
		}
	}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	if(this != NULL)
	{
		if(addNode(this, this->size, pElement) == 0) // Enlaza el elemento con el nuevo Nodo.
		{
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	void* returnAux = NULL;
	Node* pNode = NULL; // Creo el nodo auxiliar.

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		pNode = getNode(this, index); // Obtengo el nodo.
		if(pNode != NULL)
		{
			returnAux = pNode->pElement; // Devuelve el elemento que quise.
		}
	}

	return returnAux;
}

/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
	int returnAux = -1;
	Node* pNode = NULL; // Creo el nodo auxiliar.

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		pNode = getNode(this, index); // Obtengo el nodo.
		if(pNode != NULL)
		{
			pNode->pElement = pElement; // Modifico el elemento del nodo.
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this, int index)
{
	int returnAux = -1;
	Node* pNode = NULL; // Creo el nodo auxiliar.
	Node* pPrevNode = NULL; // Uso Nodo previo si nodeIndex > 0

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		pNode = getNode(this, index); // Obtengo el nodo.
		if(pNode != NULL)
		{
			if(index == 0)
			{
				this->pFirstNode = NULL; // Elimino enlace desde la cabezera (this).
				free(pNode); // Libero memoria del nodo.
				this->size--;
				returnAux = 0;
			}
			else
			{
				pPrevNode = getNode(this, (index - 1)); // Que me traiga el ultimo nodo, traigo el anterior.
				if(pPrevNode != NULL)
				{
					pPrevNode->pNextNode = pNode->pNextNode; // Del nodo, reapunto al proximo (no al nodo a eliminar)
					pNode->pNextNode = NULL; // Elimino enlace.
					free(pNode); // Libero memoria del nodo.
					this->size--;
					returnAux = 0;
				}
			}
		}
	}

	return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL)
	{
		for(int i = 0; i < ll_len(this); i++) // Recorro la lista enlazada.
		{
			if(ll_remove(this, i) == 0) // Itero cada indice para borrar los nodos.
			{
				returnAux = 0;
			}
		}
	}

	return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL)
	{
		if(ll_clear(this) == 0) // Limpia los nodos.
		{
			this = NULL; // Pongo en NULL la misma lista.
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	void* pElementCompare = NULL; // Creo el elemento auxiliar de lo que voy a obtener para compararlo.

	if(this != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pElementCompare = ll_get(this, i); // Itero los elementos.
			if(pElementCompare == pElement)
			{
				returnAux = i; // Retorno el indice/posicion si coincide.
				break;
			}
		}
	}

	return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL)
	{
		if(ll_len(this) == 0) // El mismo ll_len me dice si hay algo.
		{
			returnAux = 1; // Esta vacia.
		}
		else
		{
			returnAux = 0; // No esta vacia.
		}
	}

	return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	int returnAux = -1;

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		if(addNode(this, index, pElement) == 0) // Inserto en la posicion indicada.
		{
			returnAux = 0;
		}
	}

	return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	void* returnAux = NULL;
	void* pElement = NULL;

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		pElement = ll_get(this, index);
		if(ll_remove(this, index) == 0) // Borra/Libera el nodo.
		{
			returnAux = pElement; // Pero devuelve el elemento ya suelto (para guardar hay que castear).
		}
	}

	return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
 */
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;

	if(this != NULL)
	{
		// Implementando ll_indexOf que devuelve el indice, puedo ver si lo contiene.
		if(ll_indexOf(this, pElement) >= 0)
		{
			returnAux = 1; // Contiene.
		}
		else
		{
			returnAux = 0; // No contiene.
		}
	}

	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
 */
int ll_containsAll(LinkedList* this, LinkedList* this2)
{
	int returnAux = -1;
	void* pElement = NULL;

	//printf("Llego this: %p, this2: %p\n",this, this2);
	//printf("Salio de la linea\n");

	if(this != NULL && this2 != NULL)
	{
		returnAux = 1; // En caso de que todo este igual.

		for(int i = 0; i < ll_len(this2); i++) // Recorro la 2da lista con la lista original.
		{
			pElement = ll_get(this2, i); // De los elementos que obtengo de la lista2.
			if(pElement != NULL)
			{
				if(ll_contains(this, pElement) == 0) // Veo si lo contiene con la lista original.
				{
					returnAux = 0;
					break;
				}
			}
		}
	}

	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
 */
LinkedList* ll_subList(LinkedList* this, int from, int to)
{
	LinkedList* cloneArray = NULL;
	void* pElement = NULL;

	if(this != NULL && from >= 0 && to <= ll_len(this))
	{
		cloneArray = ll_newLinkedList(); // Creo nueva lista.
		if(cloneArray != NULL)
		{
			for(int i = from; i < to; i++) // Itero desde el comienzo hasta el final
			{
				pElement = ll_get(this, i);
				if(pElement != NULL)
				{
					ll_add(cloneArray, pElement); // Agrego los elementos a la nueva sublista.
				}
			}
		}
	}

	return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
 */
LinkedList* ll_clone(LinkedList* this)
{
	LinkedList* cloneArray = NULL;

	if(this != NULL)
	{
		cloneArray = ll_newLinkedList(); // Creo nueva lista.
		if(cloneArray  != NULL)
		{
			cloneArray = this; // Copio/Clono la lista original.
		}
	}

	return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*, void*), int order)
{
	int returnAux = -1;
	void *pNode1 = NULL;
	void *pNode2 = NULL;
	int flagSwap = 0;

	if(this != NULL && pFunc != NULL && (order == 1 || order == 0)) {
		do {
			flagSwap = 1;
			for(int i = 0 ; i < ll_len(this) - 1 ; i++)
			{
				pNode1 = ll_get(this, i); // Obtengo el primer nodo.
				pNode2 = ll_get(this, i + 1); // Obtengo el siguiente nodo.

				if(pNode1 != NULL && pNode2 != NULL)
				{
					if(
							(order == 1 && pFunc(pNode1, pNode2) > 0) ||
							(order == 0 && pFunc(pNode1, pNode2) < 0)
					)
					{
						flagSwap = 0;
						ll_set(this, i, pNode2);
						ll_set(this, i + 1, pNode1);
					}
				}
			}
		} while(flagSwap == 0);
		returnAux = 0;
	}
	return returnAux;
}

// Funciones agregadas:

/** \brief Recorre la lista y utiliza la funcion criterio recibida como parametro
 *         para multiples usos.
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        ( 0) Si ok
 */
int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux = -1;
	void *pElement = NULL;

	if(this != NULL)
	{
		for(int i = 0 ; i < ll_len(this); i++)
		{
			pElement = ll_get(this, i);
			if(pElement != NULL && pFunc(pElement) == 0) // Implemento cualquier funcion criterio
			{
				returnAux = 0;
			}
		}
	}

	return returnAux;
}

/** \brief Filtra o remueve la lista utilizando la funcion criterio recibida como parametro.
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        ( 0) Si ok
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int returnAux = -1;
	void* pElement;
	int option;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = ll_len(this) - 1; i >= 0; i--) // Uso iteracion decremental
		{
			pElement = ll_get(this, i); // Obtengo los elementos.
			if(pElement != NULL)
			{
				option = pFunc(pElement); // Me determina el criterio.
				if(option == 0)
				{
					returnAux = ll_remove(this, i); // Lo filtro/Remuevo
				}
			}
		}
	}
	return returnAux;
}

/** \brief Reduce una lista a un numero/valor (en formato int),
 *         utilizando la funcion criterio recibida como parametro.
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param pResult int Puntero con el valor a retonar (valor de la acumulacion).
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL.
                        ( 0) Si ok
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void* pElement), int* pResult)
{
	int returnAux = -1;
	int accumulator = 0; // Inicializo el acumulador.
	void* pElement = NULL;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pElement = ll_get(this, i);
			accumulator = accumulator + pFunc(pElement);
		}
		returnAux = 0; // Ok, realizo la acumulacion.
		*pResult = accumulator; // Lo guardo y lo devuelvo.
	}

	return returnAux;
}

/** \brief Reduce una lista a un numero/valor (en formato float),
 *         utilizando la funcion criterio recibida como parametro.
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param pResult float Puntero con el valor a retonar (valor de la acumulacion).
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL.
                        ( 0) Si ok
 */
int ll_reduceFloat(LinkedList* this, float (*pFunc)(void* pElement), float* pResult)
{
	int returnAux = -1;
	float accumulator = 0; // Inicializo el acumulador.
	void* pElement = NULL;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pElement = ll_get(this, i);
			accumulator = accumulator + pFunc(pElement);
		}
		returnAux = 0; // Ok, realizo la acumulacion.
		*pResult = accumulator; // Lo guardo y lo devuelvo.
	}

	return returnAux;
}







