El día 3 nos plantea extraer las expresiones mul(x,y) de un archivo, multiplicar sus valores y sumar todos los resultados. Para ello, hemos optado por utilizar un árbol binario aprovechando este tipo de estructura para almacenar los valores de manera jerárquica, lo cual resulta muy útil para recorrer y buscar datos de forma ordenada.

Este árbol consta de nodos que almacenan un valor entero (dato) correspondiente al resultado de cada operación mul(x,y) y de dos punteros (izq y der) a los subárboles izquierdo y derecho.

A partir de ahí encontramos la función crearNodo, en la que se crea un nuevo nodo vacío con un valor asignado, inicializando los punteros a nullptr. Además también encontramos la función insertarNodo, la cual inserta un valor en el árbol. Si el árbol está vacío, crea un nuevo nodo como raíz. Si no, compara el valor con la raíz para decidir si debe colocarse en el subárbol izquierdo o derecho, garantizando que el árbol mantenga su orden.

La siguiente función es sumarNodos, que recorre el árbol de manera recursiva para sumar todos los valores almacenados en los nodos, devolviendo la suma total. Tras esta, encontramos la función booleana esNumeroValido, que comprueba si el string es un número válido.

Y, por último, la función operacionMul, que procesa las operaciones mul(x, y) encontradas en el archivo. Esto lo hace extrayendo los valores x e y y calculado su producto. El resultado lo inserta en el árbol y repite el proceso para todas las expresiones del archivo, habiendo comprobado con la función esnUmeroValido que los números sean válidos.

A continuación, se ejecuta el main, donde se abre el archivo de entrada (input.txt). Finalmente, se incializa un árbol vacío y se llama a las funciones operacionMul y sumarNodos para obtener la suma total de los valores en el árbol, que será el resultado final del problema.