/**
 * Structures
 **/
STRUCT Matrix
	row : INTEGER
	col : INTEGER
	emptyVal :INTEGER
	data : POINTER<STRUCT ArrayList>

/**
 * Subprograms
 **/


/**
 * Entry point
 **/
PROCEDURE main()
VAR
	testStats : POINTER<STRUCT TestStats>
	matrix : POINTER<STRUCT Matrix>
	pval:POINTER<FLOAT>
BEGIN
/*	pval<-ALLOC(FLOAT)
	matrix <- newMatrix(3,3,0)
	removeRow(matrix,1)
	removeColumn(matrix,1)
	addRow(matrix,1)
	addColumn(matrix,1)

	setValue(matrix,1,2,36) 
	getValue(matrix,1,2,pval)
PRINT(CONTENT(pval))*/
	testStats <- newTestStats(429)
	
	/*** cas d'erreur avec pointeur NULL ***/
	nullPointerTests(testStats)
	
	/*** cas d'erreur avec dimensions invalides ***/
	newMatrixTests(2, -1, 0, testStats)
	newMatrixTests(-1, 3, 0, testStats)	
	newMatrixTests(-1, -1, 0, testStats)	
	
	/*** Cycle de vie d'une matrice avec diffÃ©rentes dimensions de dÃ©part ***/
	
	matrixLifeCycleTests(0, 0, 0, testStats)
	matrixLifeCycleTests(2, 0, 0, testStats)
	matrixLifeCycleTests(0, 3, 0, testStats)
	matrixLifeCycleTests(2, 3, 0, testStats)
	
	/*** Affichage des statistiques sur la campagne de tests ***/
	printTestStats(testStats)	

	FREE(testStats)
	
END


// Tests relatifs au cycle de vue d'une matrice : crÃ©ation, ajout/suppression de lignes/colonnes, modification de coefficients, destruction
PROCEDURE matrixLifeCycleTests(rows : INTEGER, cols : INTEGER, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>)
VAR
	m : POINTER<STRUCT Matrix>
	defVal : FLOAT
BEGIN
	m <- newMatrixTests(rows, cols, defVal, testStats)	// Tests relatifs Ã  la crÃ©ation de la matrice
	printMatrix(m)
	
	getEmptyValue(m, ADDRESS(defVal))
	
	badAccessTests(m, testStats)			// Tests relatifs Ã  l'utilisation de {get/set}value avec des indices invalides
	
	setValueTests(m, testStats)				// Tests relatifs Ã  la modification de tous les coefficients
	printMatrix(m)
	
	addColumnsTests(m, defVal, testStats)	// Tests relatifs Ã  l'ajout de colonnes
	printMatrix(m)
	
	removeColumnsTests(m, testStats)		// Tests relatifs Ã  la suppression de colonnes
	printMatrix(m)
	
	addRowsTests(m, defVal, testStats)		// Tests relatifs Ã  l'ajout de lignes
	printMatrix(m)
	
	removeRowsTests(m, testStats)			// Tests relatifs Ã  la suppression de lignes
	printMatrix(m)	
	
	deleteMatrixTests(m, testStats)			// Tests relatifs Ã  la destruction de la matrice
	
END


// Tests relatifs Ã  la destruction d'une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
PROCEDURE deleteMatrixTests(m : POINTER<STRUCT Matrix>, testStats : POINTER<STRUCT TestStats>)
VAR 
	success : BOOLEAN
BEGIN
	success <- deleteMatrix(m)
	
	PRINT( "deleteMatrix doit rÃ©ussir avec une matrice diffÃ©rente de NULL : " )
	printTestStatus( success , testStats )	

END


// Tests relatifs Ã  la suppression de lignes dans une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
PROCEDURE removeRowsTests(m : POINTER<STRUCT Matrix>, testStats : POINTER<STRUCT TestStats>)
BEGIN
	removeRowTests(m,0,testStats)					// dÃ©but
	removeRowTests(m,getRows(m)/2,testStats)		// milieu
	removeRowTests(m,getRows(m)-1,testStats)		// fin
	
	// cas d'erreur
	removeRowTests(m,-1,testStats)					// avant le dÃ©but
	removeRowTests(m,getRows(m),testStats)			// aprÃ¨s la fin 
END


// Tests relatifs Ã  la suppression d'une ligne dans une matrice
PROCEDURE removeRowTests(m : POINTER<STRUCT Matrix>, rowIndex : INTEGER, testStats : POINTER<STRUCT TestStats>) 
VAR
	success : BOOLEAN
	rows : INTEGER
BEGIN
	rows <- getRows(m)
	success <- removeRow(m,rowIndex)
	
	IF(rowIndex >= rows OR rowIndex < 0) THEN
		PRINT( "removeRow doit Ã©chouer avec l'indice " )
		PRINT( rowIndex )
		PRINT( " : " )
		printTestStatus( success = FALSE, testStats )
		PRINT( "Le nombre de lignes de la matrice n'a pas changÃ© : " )
		printTestStatus( rows = getRows(m), testStats )	
	ELSE
		PRINT( "removeRow doit rÃ©ussir avec l'indice " )
		PRINT( rowIndex )
		PRINT( " : " )
		printTestStatus( success , testStats )
		PRINT( "Le nombre de lignes de la matrice a Ã©tÃ© dÃ©crÃ©mentÃ© : " )
		printTestStatus( rows-1 = getRows(m), testStats )	
	END_IF
END


// Tests relatifs Ã  l'ajout de lignes dans une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
PROCEDURE addRowsTests(m : POINTER<STRUCT Matrix>, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>)
BEGIN
	addRowTests(m,0,defVal,testStats)					// dÃ©but
	addRowTests(m,getRows(m)/2,defVal,testStats)		// milieu
	addRowTests(m,getRows(m),defVal,testStats)			// fin
	
	// cas d'erreur
	addRowTests(m,-1,defVal,testStats)					// avant le dÃ©but
	addRowTests(m,getRows(m)+1,defVal,testStats)		// aprÃ¨s la fin 
		
END


// Tests relatifs Ã  l'ajout d'une ligne dans une matrice
PROCEDURE addRowTests(m : POINTER<STRUCT Matrix>, rowIndex : INTEGER, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>) 
VAR
	success : BOOLEAN
	rows : INTEGER
	newVal : FLOAT
BEGIN
	rows <- getRows(m)
	success <- addRow(m,rowIndex)
	newVal <- 42
	
	IF(rowIndex > rows OR rowIndex < 0) THEN
		PRINT( "addRow doit Ã©chouer avec l'indice " )
		PRINT( rowIndex )
		PRINT( " : " )
		printTestStatus( success = FALSE, testStats )
		PRINT( "Le nombre de lignes de la matrice n'a pas changÃ© : " )
		printTestStatus( rows = getRows(m), testStats )	
	ELSE
		PRINT( "addRow doit rÃ©ussir avec l'indice " )
		PRINT( rowIndex )
		PRINT( " : " )
		printTestStatus( success , testStats )
		PRINT( "Le nombre de lignes de la matrice a Ã©tÃ© incrÃ©mentÃ© : " )
		printTestStatus( rows+1 = getRows(m), testStats )
		
		PRINTLN( "Une nouvelle ligne est apparue avec la valeur par dÃ©faut : ")
		coeffTests(m, FALSE, rowIndex, rowIndex, 0, getColumns(m)-1, defVal, testStats)		
	
		PRINT( "On met la valeur " )
		PRINT( newVal )
		PRINTLN( " dans la nouvelle ligne et on vÃ©rifie que les affectations se sont bien dÃ©roulÃ©es : ")
		coeffTests(m, TRUE, rowIndex, rowIndex, 0, getColumns(m)-1, newVal, testStats)			
	END_IF		
END


// Tests relatifs Ã  la suppression de colonnes dans une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
PROCEDURE removeColumnsTests(m : POINTER<STRUCT Matrix>, testStats : POINTER<STRUCT TestStats>)
BEGIN
	removeColumnTests(m,0,testStats)					// dÃ©but
	removeColumnTests(m,getColumns(m)/2,testStats)		// milieu
	removeColumnTests(m,getColumns(m)-1,testStats)		// fin
	
	// cas d'erreur
	removeColumnTests(m,-1,testStats)					// avant le dÃ©but
	removeColumnTests(m,getColumns(m),testStats)		// aprÃ¨s la fin 
		
END


// Tests relatifs Ã  la suppression d'une colonne dans une matrice
PROCEDURE removeColumnTests(m : POINTER<STRUCT Matrix>, colIndex : INTEGER, testStats : POINTER<STRUCT TestStats>) 
VAR
	success : BOOLEAN
	cols : INTEGER
BEGIN
	cols <- getColumns(m)
	success <- removeColumn(m,colIndex)
	
	IF(colIndex >= cols OR colIndex < 0) THEN
		PRINT( "removeColumn doit Ã©chouer avec l'indice " )
		PRINT( colIndex )
		PRINT( " : " )
		printTestStatus( success = FALSE, testStats )
		PRINT( "Le nombre de colonnes de la matrice n'a pas changÃ© : " )
		printTestStatus( cols = getColumns(m), testStats )	
	ELSE
		PRINT( "removeColumn doit rÃ©ussir avec l'indice " )
		PRINT( colIndex )
		PRINT( " : " )
		printTestStatus( success , testStats )
		PRINT( "Le nombre de colonnes de la matrice a Ã©tÃ© dÃ©crÃ©mentÃ© : " )
		printTestStatus( cols-1 = getColumns(m), testStats )	
	END_IF
	
		
END


// Tests relatifs Ã  l'utilisation de {get/set}value avec des indices invalides
PROCEDURE badAccessTests(m : POINTER<STRUCT Matrix>, testStats : POINTER<STRUCT TestStats>)
VAR
	rows, cols : INTEGER
BEGIN
	rows <- getRows(m)
	cols <- getColumns(m)
	badAccessTest(m, -1, -1, testStats)
	badAccessTest(m, rows/2, -1, testStats)
	badAccessTest(m, -1, cols/2, testStats)
	badAccessTest(m, rows/2, cols, testStats)
	badAccessTest(m, rows, cols/2, testStats)
	badAccessTest(m, rows, cols, testStats)
END

// Tests relatifs Ã  l'utilisation de {get/set}value avec un indice invalide
PROCEDURE badAccessTest(m : POINTER<STRUCT Matrix>, i : INTEGER, j : INTEGER, testStats : POINTER<STRUCT TestStats>)
VAR
	success : BOOLEAN
BEGIN
	PRINT( "setValue doit Ã©chouer sur le coefficient (" )
	PRINT( i )
	PRINT( "," )
	PRINT( j )
	PRINT( ") : " )
	success <- setValue(m, i, j, 42)	
	printTestStatus( success = FALSE, testStats )	
	
	PRINT( "getValue doit Ã©chouer sur le coefficient (" )
	PRINT( i )
	PRINT( "," )
	PRINT( j )
	PRINT( ") : " )
	success <- getValue(m, i, j, NULL)	
	printTestStatus( success = FALSE, testStats )		
END


// Tests relatifs Ã  l'ajout de colonnes dans une matrice : au dÃ©but, au milieu, Ã  la fin + cas d'erreur
PROCEDURE addColumnsTests(m : POINTER<STRUCT Matrix>, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>)
BEGIN
	addColumnTests(m,0,defVal,testStats)					// dÃ©but
	addColumnTests(m,getColumns(m)/2,defVal,testStats)		// milieu
	addColumnTests(m,getColumns(m),defVal,testStats)		// fin
	
	// cas d'erreur
	addColumnTests(m,-1,defVal,testStats)					// avant le dÃ©but
	addColumnTests(m,getColumns(m)+1,defVal,testStats)		// aprÃ¨s la fin 
END


// Tests relatifs Ã  l'ajout d'une colonne dans une matrice
PROCEDURE addColumnTests(m : POINTER<STRUCT Matrix>, colIndex : INTEGER, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>) 
VAR
	success : BOOLEAN
	cols : INTEGER
	newVal : FLOAT
BEGIN
	cols <- getColumns(m)
	success <- addColumn(m,colIndex)
	newVal <- 404
	
	IF(colIndex > cols OR colIndex < 0) THEN
		PRINT( "addColumn doit Ã©chouer avec l'indice " )
		PRINT( colIndex )
		PRINT( " : " )
		printTestStatus( success = FALSE, testStats )
		PRINT( "Le nombre de colonnes de la matrice n'a pas changÃ© : " )
		printTestStatus( cols = getColumns(m), testStats )	
	ELSE
		PRINT( "addColumn doit rÃ©ussir avec l'indice " )
		PRINT( colIndex )
		PRINT( " : " )
		printTestStatus( success , testStats )
		PRINT( "Le nombre de colonnes de la matrice a Ã©tÃ© incrÃ©mentÃ© : " )
		printTestStatus( cols+1 = getColumns(m), testStats )
		
		PRINTLN( "Une nouvelle colonne est apparue avec la valeur par dÃ©faut : ")
		coeffTests(m, FALSE,  0, getRows(m)-1, colIndex, colIndex, defVal, testStats)		
		
		PRINT( "On met la valeur " )
		PRINT( newVal )
		PRINTLN( " dans la nouvelle colonne et on vÃ©rifie que les affectations se sont bien dÃ©roulÃ©es : ")
		coeffTests(m, TRUE,  0, getRows(m)-1, colIndex, colIndex, newVal, testStats)		
	END_IF	
END

// Tests relatifs Ã  la modification de tous les coefficients dans une matrice
PROCEDURE setValueTests(m : POINTER<STRUCT Matrix>, testStats : POINTER<STRUCT TestStats>)
VAR
	i, j: INTEGER
	rows, cols : INTEGER
	value : FLOAT
	retrievedValue : FLOAT
	success : BOOLEAN
BEGIN
	PRINTLN( "Changement de tous les coefficiants de la matrice : " )

	rows <- getRows(m)
	cols <- getColumns(m)

	FOR i FROM 0 TO rows-1 DO
		FOR j FROM 0 TO cols-1 DO
			value <- 1 + j + cols * i
			coeffTests(m, TRUE, i, i, j, j, value, testStats)	
		END_FOR	
	END_FOR
END


// Tests relatifs Ã  la rÃ©cupÃ©ration et/ou la modification d'une partie des coefficients d'une matrice
PROCEDURE coeffTests(m : POINTER<STRUCT Matrix>, callSetValue : BOOLEAN, rowMin : INTEGER, rowMax : INTEGER, colMin : INTEGER, colMax : INTEGER, expectedValue : FLOAT, testStats : POINTER<STRUCT TestStats>)
VAR
	m : POINTER<STRUCT Matrix>
	coeff : FLOAT
	success : BOOLEAN
	i, j : INTEGER

BEGIN
	FOR i FROM rowMin TO rowMax DO
		FOR j FROM colMin TO colMax DO
	
			IF(callSetValue) THEN
				PRINT( "setValue doit rÃ©ussir sur le coefficient (" )
				PRINT( i )
				PRINT( "," )
				PRINT( j )
				PRINT( ") : " )
				success <- setValue(m, i, j, expectedValue )	
				printTestStatus( success , testStats )	
			END_IF
			
			coeff <- -1
			PRINT( "getValue doit rÃ©ussir sur le coefficient (" )
			PRINT( i )
			PRINT( "," )
			PRINT( j )
			PRINT( ") : " )
			success <- getValue(m, i, j, ADDRESS(coeff) )
			printTestStatus( success , testStats )	

			PRINT( "getValue doit modifier la valeur du flottant fourni Ã  " )
			PRINT( expectedValue )
			PRINT( " : " )			
			printTestStatus( coeff = expectedValue, testStats )		
			
		END_FOR
	END_FOR	
END

// Tests relatifs Ã  la crÃ©ation d'une matrice
FUNCTION newMatrixTests(rows : INTEGER, cols : INTEGER, defVal : FLOAT, testStats : POINTER<STRUCT TestStats>) : POINTER<STRUCT Matrix>
VAR
	m : POINTER<STRUCT Matrix>
	coeff : FLOAT
	retrievedRows, retrievedCols : INTEGER
	success : BOOLEAN
	i, j : INTEGER

BEGIN
	coeff <- -1
	m <- newMatrix(rows, cols, defVal)
	
	IF(rows >= 0 AND cols >= 0) THEN
		PRINT( "L'appel Ã  newMatrix avec les dimenstions ")
		PRINT( rows )
		PRINT( " et ")
		PRINT( cols )
		PRINT( " ne doit pas renvoyer NULL : ")
		printTestStatus( m != NULL, testStats )	
		
		retrievedRows <- getRows(m)
		PRINT( "getRows doit retourner " )
		PRINT( rows )
		PRINT( " : " )
		printTestStatus( getRows(m) = rows, testStats )	
		
		retrievedCols <- getColumns(m)
		PRINT( "getCols doit retourner " )
		PRINT( cols )
		PRINT( " : " )
		printTestStatus( getColumns(m) = cols, testStats )		
		
		success <- getEmptyValue(m, ADDRESS(coeff) )
		PRINT( "getEmptyValue doit rÃ©ussir : " )
		printTestStatus( success , testStats )				
		PRINT( "getEmptyValue doit modifier la valeur du flottant fourni Ã  " )
		PRINT( defVal )
		PRINT( " : " )
		printTestStatus( coeff = defVal, testStats )
		
		PRINTLN( "Tous les coefficients de la matrice doivent Ãªtre Ã©gaux Ã  la valeur par dÃ©faut : " )
		coeffTests(m, 0, FALSE,  rows-1, 0, cols-1, defVal, testStats)

	ELSE
		PRINT( "L'appel Ã  newMatrix avec les dimenstions ")
		PRINT( rows )
		PRINT( " et ")
		PRINT( cols )
		PRINT( " doit renvoyer NULL : ")
		printTestStatus( m = NULL, testStats )		
	END_IF
	
	RETURN m
END

// Cas d'erreurs avec pointeur NULL
PROCEDURE nullPointerTests(testStats : POINTER<STRUCT TestStats>)
VAR
	m : POINTER<STRUCT Matrix>
	coeff : FLOAT

BEGIN
	m <- NULL
	coeff <- 42
	
	PRINTLN("Toutes les opÃ©rations doivent Ã©chouer avec un pointeur NULL : ")
	
	PRINT( "getColumns : " )
	printTestStatus( getColumns(m) = -1, testStats )
	
	PRINT( "getRows : " )
	printTestStatus( getRows(m) = -1, testStats )	
	
	PRINT( "deleteMatrix : " )
	printTestStatus( deleteMatrix(m) = FALSE, testStats )		
	
	PRINT( "getEmptyValue : " )
	printTestStatus( getEmptyValue(m, ADDRESS(coeff) ) = FALSE, testStats )	
	
	PRINT( "Le flottant fourni n'a pas Ã©tÃ© modifiÃ© par getEmptyValue : ")
	printTestStatus( coeff = 42, testStats )	
	
	PRINT( "On doit pouvoir mettre NULL en dernier argument de getEmptyValue : " )
	printTestStatus( getEmptyValue(m, NULL ) = FALSE, testStats )	
	
	PRINT( "getValue : " )
	printTestStatus( getValue(m, 0, 0, ADDRESS(coeff) ) = FALSE, testStats )	
	
	PRINT( "Le flottant fourni n'a pas Ã©tÃ© modifiÃ© par getValue : ")
	printTestStatus( coeff = 42, testStats )	
	
	PRINT( "On doit pouvoir mettre NULL en dernier argument de getValue : " )
	printTestStatus( getEmptyValue(m, NULL ) = FALSE, testStats )		
	
	PRINT( "setValue : " )
	printTestStatus( setValue(m, 0, 0, 0.0) = FALSE, testStats )			
	
	PRINT( "addRow : " )
	printTestStatus( addRow(m, 0) = FALSE, testStats )	
	
	PRINT( "removeRow : " )
	printTestStatus( removeRow(m, 0) = FALSE, testStats )		
	
	
	PRINT( "addColumn : " )
	printTestStatus( addColumn(m, 0) = FALSE, testStats )	
	
	PRINT( "removeColumn : " )
	printTestStatus( removeColumn(m, 0) = FALSE, testStats )	
END


// ======================= STATISTIQUES SUR LES TESTS ===============================

STRUCT TestStats
	passed : INTEGER
	failed : INTEGER
	done : INTEGER
	planned : INTEGER

FUNCTION newTestStats(planned : INTEGER) : POINTER<STRUCT TestStats>
VAR
	testStats : POINTER<STRUCT TestStats>
BEGIN
	testStats <- ALLOC( STRUCT TestStats )
	testStats->planned <- planned	
	testStats->passed <- 0
	testStats->failed <- 0
	testStats->done <- 0
	RETURN testStats
END

PROCEDURE printTestStats(testStats : POINTER<STRUCT TestStats>)
BEGIN
	IF(testStats != NULL) THEN
		PRINTLN("****** Test stats *******")
		PRINT("Planned : ")
		PRINTLN(testStats->planned)
		PRINT("Passed : ")
		PRINTLN(testStats->passed)	
		PRINT("Failed : ")
		PRINTLN(testStats->failed)	
		PRINT("Missed : ")
		PRINTLN(testStats->planned - testStats->done)	
	END_IF
END

PROCEDURE printTestStatus(expectedEqualsActual: BOOLEAN, testStats : POINTER<STRUCT TestStats>)
BEGIN
		
	IF(testStats != NULL) THEN	
		testStats->done <- testStats->done + 1
		
		IF(expectedEqualsActual) THEN
			testStats->passed <- testStats->passed + 1
			PRINTLN("PASSED")
		ELSE
		    testStats->failed <- testStats->failed + 1
		    PRINTLN("FAILED")
		END_IF		
		
	END_IF
END


// =========================== TYPE ABSTRAIT MATRIX ===================================

/* Returns a pointer on a newly allocated matrix of containing rows x cols coefficients, 
initialized with the default value defVal. By convention, returns NULL on problem. */
FUNCTION newMatrix(rows: INTEGER, cols: INTEGER, defVal: FLOAT): POINTER<STRUCT Matrix>
VAR
	matrix:POINTER<STRUCT Matrix>
	row:POINTER<STRUCT ArrayList>
	index,index2 : INTEGER
BEGIN
	
	IF(matrix = NULL OR cols < 0 OR rows < 0) THEN
		RETURN NULL
	END_IF
	matrix <- ALLOC(STRUCT Matrix)
	matrix->data<- newArrayList(rows)
	FOR index FROM 0 TO rows-1 DO
		row<-newArrayList(cols)
		FOR index2 FROM 0 TO cols -1 DO
			set(row,index2,NULL)
		END_FOR
		set(matrix->data,index,row)
	END_FOR
	matrix->row<-rows
	matrix->col<-cols
	matrix->emptyVal <- 0
	RETURN matrix
	
	
END

//  Deallocates the matrix pointed by m in memory. Returns TRUE on success, FALSE otherwise.
FUNCTION deleteMatrix(m: POINTER<STRUCT Matrix>) : BOOLEAN
VAR
index:INTEGER
tmp:INTEGER
BEGIN
	
	IF(m != NULL)THEN
		tmp <- m->row
		FOR index FROM 0 TO tmp-1 DO
			removeRow(m,0)
		END_FOR
		deleteArrayList(m->data)
		FREE(m)
		
		RETURN TRUE
	END_IF
	RETURN FALSE
	
END


// Returns the number of columns stored in the matrix pointed by m. By convention, returns -1 on problem.
FUNCTION getColumns(m: POINTER<STRUCT Matrix>) : INTEGER
BEGIN
	IF(m != NULL)THEN
		RETURN m->col
	ELSE
		RETURN -1
	END_IF
END

// Returns the number of rows stored in the matrix pointed by m. By convention, returns -1 on problem.
FUNCTION getRows(m: POINTER<STRUCT Matrix>) : INTEGER
BEGIN
	IF(m != NULL)THEN
		RETURN m->row
	ELSE
		RETURN -1
	END_IF
END


// Gets the value modeling an empty cell in the matrix pointed by m. Returns TRUE on success, FALSE otherwise
FUNCTION getEmptyValue(m: POINTER<STRUCT Matrix>, pval: POINTER<FLOAT>) : BOOLEAN
BEGIN
	IF(m != NULL AND pval!=NULL)THEN
		CONTENT(pval)<-m->emptyVal
		RETURN TRUE
	ELSE
		RETURN FALSE
	END_IF
		
END


// Gets the value at the specified row and column in the matrix pointed by m. Returns TRUE on success, FALSE otherwise
FUNCTION getValue(m: POINTER<STRUCT Matrix>, row: INTEGER, col: INTEGER, pval: POINTER<FLOAT>) : BOOLEAN
VAR
rows: POINTER<POINTER<STRUCT ArrayList>>
cell:POINTER<POINTER<FLOAT>>
BEGIN
	IF(m=NULL OR row < 0 OR row >= m->row OR col >= m->col OR col<0 OR pval=NULL)THEN
		RETURN FALSE
	END_IF
	rows<-ALLOC(POINTER<STRUCT ArrayList>)
	cell<-ALLOC(POINTER<FLOAT>)
	getValueAt(m->data,row,rows)
	getValueAt(CONTENT(rows),col,cell)
	IF(CONTENT(cell)=NULL)THEN
		CONTENT(pval)<-m->emptyVal
	ELSE
		CONTENT(pval)<-CONTENT(CONTENT(cell))
	END_IF
	FREE(rows)
	FREE(cell)
	RETURN TRUE
END


// Sets the value at the specified row and column to val in the matrix pointed by m. Returns TRUE on success, FALSE otherwise
FUNCTION setValue(m : POINTER<STRUCT Matrix>, row: INTEGER, col: INTEGER, val: FLOAT) : BOOLEAN
VAR

rows: POINTER<POINTER<STRUCT ArrayList>>
cell:POINTER<POINTER<FLOAT>>
pval:POINTER<FLOAT>
BEGIN
	IF(m=NULL OR row < 0 OR row >= m->row OR col >=m->col OR col<0)THEN
		RETURN FALSE
	END_IF
	rows<-ALLOC(POINTER<STRUCT ArrayList>)
	cell<-ALLOC(POINTER<FLOAT>)
	pval<-ALLOC(FLOAT)
	getValueAt(m->data,row,rows)
	getValueAt(CONTENT(rows),col,cell)
	IF(val!=m->emptyVal)THEN
		IF(CONTENT(cell)=NULL)THEN
			CONTENT(pval)<-val
			CONTENT(cell)<-pval
			set(CONTENT(rows),col,CONTENT(cell))
			
		ELSE
			CONTENT(CONTENT(cell))<-val
			FREE(pval)
		END_IF
	ELSE
		IF(CONTENT(cell)!=NULL)THEN
			FREE(CONTENT(CONTENT(cell)))
			set(CONTENT(rows),col,NULL)
		END_IF
	END_IF
	FREE(rows)
	FREE(cell)
	
	RETURN TRUE
END


/* Inserts a row at the specified index in the matrix pointed by m.
Rows initially present at indices >= rowIndex are shifted.
The new row is filled with the default value.
Returns TRUE on success, FALSE otherwise. */
FUNCTION addRow(m: POINTER<STRUCT Matrix>, rowIndex: INTEGER) : BOOLEAN
VAR
index: INTEGER
row: POINTER<STRUCT ArrayList>
BEGIN
	IF(m=NULL OR rowIndex < 0 OR rowIndex >m->row)THEN
		RETURN FALSE
	END_IF
	row<-newArrayList(m->col)
	insert(m->data,rowIndex,row)
	FOR index FROM 0 TO m->col-1 DO
		set(row,index,NULL)
	END_FOR
	m->row<-m->row +1
	RETURN TRUE	
END



// Removes the row at the specified index in the matrix pointed by m. Returns TRUE on success, FALSE otherwise.
FUNCTION removeRow(m: POINTER<STRUCT Matrix>, rowIndex: INTEGER) : BOOLEAN
VAR
index : INTEGER
row: POINTER<POINTER<STRUCT ArrayList>>
cell:POINTER<POINTER<FLOAT>>
BEGIN
	IF(m=NULL OR rowIndex < 0 OR rowIndex >m->row -1)THEN
		RETURN FALSE
	END_IF
	row<-ALLOC(POINTER<STRUCT ArrayList>)
	cell<-ALLOC(POINTER<FLOAT>)
	getValueAt(m->data,rowIndex,row)
	FOR index FROM 0 TO m->col-1 DO
		getValueAt(CONTENT(row),index,cell)
		IF(CONTENT(cell)!= NULL)THEN
			FREE(CONTENT(cell))
		END_IF
	END_FOR
	deleteArrayList(CONTENT(row))
	remove(m->data,rowIndex)
	FREE(row)
	FREE(cell)
	m->row<-m->row -1
	RETURN TRUE
END



/* Inserts a column at the specified index in the matrix pointed by m.
Columns initially present at indices >= colIndex are shifted.
The new column is filled with the default value.
Returns TRUE on success, FALSE otherwise. */
FUNCTION addColumn(m: POINTER<STRUCT Matrix>, colIndex : INTEGER) : BOOLEAN
VAR
index : INTEGER
row: POINTER<POINTER<STRUCT ArrayList>>
BEGIN
	IF(m=NULL OR colIndex < 0 OR colIndex >m->col)THEN
		RETURN FALSE
	END_IF
	row<-ALLOC(POINTER<STRUCT ArrayList>)
	FOR index FROM 0 TO m->row -1 DO
		getValueAt(m->data,index,row)
		insert(CONTENT(row),colIndex,NULL)
	END_FOR
	FREE(row)
	m->col <- m->col +1
	RETURN TRUE
	
END


// Removes the column at the specified index in the matrix pointed by m. Returns TRUE on success, FALSE otherwise.
FUNCTION removeColumn(m: POINTER<STRUCT Matrix>, colIndex : INTEGER) : BOOLEAN
VAR
index : INTEGER
row: POINTER<POINTER<STRUCT ArrayList>>
cell:POINTER<POINTER<FLOAT>>
BEGIN
	IF(m=NULL OR colIndex < 0 OR colIndex >m->col -1)THEN
		RETURN FALSE
	END_IF
	row<-ALLOC(POINTER<STRUCT ArrayList>)
	cell<-ALLOC(POINTER<FLOAT>)
	FOR index FROM 0 TO m->row -1 DO
		getValueAt(m->data,index,row)
		getValueAt(CONTENT(row),colIndex,cell)
		IF(CONTENT(cell)!= NULL)THEN
			FREE(CONTENT(cell))
		END_IF
		remove(CONTENT(row),colIndex)
	END_FOR
	FREE(row)
	FREE(cell)
	m->col <- m->col -1
	RETURN TRUE	
END

// -------- Utility functions ---------

PROCEDURE printMatrix(m : POINTER<STRUCT Matrix>)
VAR
	success : BOOLEAN
	rows, cols, i, j : INTEGER
	coeff : FLOAT
BEGIN

	IF(m != NULL) THEN
		PRINTLN("Etat de la matrice :")
		rows <- getRows(m)
		cols <- getColumns(m)
		
		FOR i FROM 0 TO rows-1 DO
			FOR j FROM 0 TO cols-1 DO
				success <- getValue(m, i, j, ADDRESS(coeff) )
				
				IF(success) THEN
					PRINT(coeff)
				ELSE
					PRINT("x")
				END_IF
				
				PRINT(" ")
			END_FOR
			PRINTLN("")
		END_FOR
		
		PRINTLN("")
	END_IF
END


// ====================== TYPE ABSTRAIT ARRAYLIST GENERIQUE =======================

/**
 * Structures
 **/
STRUCT ArrayList
	values:POINTER<POINTER>
	size:INTEGER

/**
 * Subprograms
 **/
// Builds an empty arrayList
// returns NULL on problem
FUNCTION newArrayList(initialCapacity:INTEGER) : POINTER<STRUCT ArrayList>
VAR
	arrayList:POINTER<STRUCT ArrayList>
BEGIN
	IF(initialCapacity < 0)THEN
		RETURN NULL
	END_IF
	arrayList <- ALLOC(STRUCT ArrayList)
	IF(arrayList = NULL) THEN
		RETURN NULL
	END_IF
	arrayList->values <- ALLOC(POINTER,initialCapacity)
	arrayList->size <- initialCapacity
	RETURN arrayList
END

// Destroys the specified arrayList and returns TRUE on success.
FUNCTION deleteArrayList(arrayList: POINTER<STRUCT ArrayList>) : BOOLEAN
BEGIN
	IF( arrayList = NULL)THEN
		RETURN FALSE
	END_IF
	IF(arrayList->values != NULL )THEN
		FREE(arrayList->values)
	END_IF
	FREE(arrayList)
	RETURN TRUE
END

// Returns the number of elements stored in the specified arrayList.
// Returns -1 on problem.
FUNCTION getSize(arrayList: POINTER<STRUCT ArrayList>) : INTEGER
BEGIN
	IF(arrayList = NULL)THEN
		RETURN -1
	ELSE
		RETURN arrayList->size
	END_IF
END

// Sets the value of the ith element to the specified value in the specified arrayList.
// Returns TRUE on success.
FUNCTION set(arrayList: POINTER<STRUCT ArrayList>, index: INTEGER, value: POINTER): BOOLEAN
VAR 
	values:POINTER<POINTER>
BEGIN
	IF(arrayList = NULL OR arrayList->values = NULL OR index < 0 OR arrayList->size <= index)THEN
		RETURN FALSE
	END_IF
	values <- arrayList->values
	values[index] <- value
	RETURN TRUE
END

// get the value of the element stored in the specified arrayList at ith position.
// result stored at pValue. Returns FALSE on problem.
FUNCTION getValueAt(arrayList: POINTER<STRUCT ArrayList>, index: INTEGER, pValue:POINTER<POINTER>): BOOLEAN
VAR
	values:POINTER<POINTER>
BEGIN
	IF(arrayList = NULL OR arrayList->values = NULL OR arrayList->size <= index OR index < 0 OR pValue = NULL)THEN
		RETURN FALSE
	END_IF
	values <- arrayList->values
	CONTENT(pValue) <- values[index]
	RETURN TRUE
END


// Inserts a new element with the specified value at the ith position in the specified arrayList.
// The next elements are shifted to the right. Returns TRUE on success.
FUNCTION insert(arrayList: POINTER<STRUCT ArrayList>, index: INTEGER, value: POINTER) : BOOLEAN
VAR
	values,newArray:POINTER<POINTER>
	i:INTEGER
BEGIN
	IF ( arrayList = NULL OR index < 0 OR index > arrayList->size ) THEN
		RETURN FALSE
	END_IF
	values <- arrayList->values
	newArray <- ALLOC(POINTER,arrayList->size + 1)
	FOR i FROM 0 TO index-1 DO
		newArray[i] <- values[i]
	END_FOR
	newArray[index] <- value
	FOR i FROM index TO arrayList->size-1 DO 
		newArray[i+1] <- values[i]
	END_FOR
	arrayList->size<-arrayList->size+1
	IF(arrayList->values != NULL)THEN
		FREE(arrayList->values)
	END_IF
	arrayList->values <- newArray
	RETURN TRUE
END

// Removes the  ith element in the specified arrayList. The next elements are shifted to the left.
// Returns TRUE on success.
FUNCTION remove(arrayList: POINTER<STRUCT ArrayList>, index: INTEGER) : BOOLEAN
VAR
	values,newArray:POINTER<POINTER>
	i:INTEGER
BEGIN
	IF ( arrayList = NULL OR arrayList->values = NULL OR index < 0 OR index >= arrayList->size ) THEN
		RETURN FALSE
	END_IF
	values <- arrayList->values
	newArray <- ALLOC(POINTER,arrayList->size - 1)
	FOR i FROM 0 TO index-1 DO
		newArray[i] <- values[i]
	END_FOR
	FOR i FROM index+1 TO arrayList->size-1 DO 
		newArray[i-1] <- values[i]
	END_FOR
	arrayList->size<-arrayList->size-1
	FREE(arrayList->values)
	IF(arrayList->size = 0)THEN
		arrayList->values <- NULL
	ELSE
		arrayList->values <- newArray
	END_IF
	RETURN TRUE
END

// Adds a new element with the specified value at the end of the specified arrayList.
// Returns TRUE on success.
FUNCTION append(arrayList: POINTER<STRUCT ArrayList>, value: POINTER) : BOOLEAN
BEGIN
	IF(arrayList = NULL)THEN
		RETURN FALSE
	END_IF
	RETURN insert(arrayList,arrayList->size,value)
END

// Builds a new arrayList, resulting from the concatenation of arrayList1 and arrayList2.
// arrayList1 and arrayList2 are left unchanged. Returns NULL on problem.
FUNCTION concatenate(arrayList1: POINTER<STRUCT ArrayList>, arrayList2: POINTER<STRUCT ArrayList>) : POINTER<STRUCT ArrayList>
VAR
	newArrayList:POINTER<STRUCT ArrayList>
	values1,values2,newValues:POINTER<POINTER>
	i:INTEGER
BEGIN
	IF ( arrayList1 = NULL OR arrayList1->values = NULL OR arrayList2 = NULL OR arrayList2->values = NULL ) THEN
		RETURN NULL
	END_IF
	newArrayList <- newArrayList(arrayList1->size+arrayList2->size)
	IF(newArrayList = NULL OR newArrayList->values = NULL)THEN
		RETURN NULL
	END_IF
	values1 <- arrayList1->values
	values2 <- arrayList2->values
	newValues <- newArrayList->values
	FOR i FROM 0 TO arrayList1->size - 1 DO
		newValues[i] <- values1[i]
	END_FOR
	FOR i FROM 0 TO arrayList2->size - 1 DO
		newValues[arrayList1->size + i] <- values2[i]
	END_FOR
	RETURN newArrayList
END

// Swaps the ith and jth elements in the specified arrayList. Returns TRUE on success.
FUNCTION swap(arrayList: POINTER<STRUCT ArrayList>, i: INTEGER, j: INTEGER) : BOOLEAN
VAR
	values:POINTER<POINTER>
	tmp:INTEGER
BEGIN
	IF ( arrayList = NULL OR arrayList->values = NULL OR i < 0 OR i > arrayList->size OR j < 0 OR j > arrayList->size ) THEN
		RETURN FALSE
	END_IF
	values <- arrayList->values
	tmp <- values[j]
	values[j] <- values[i]
	values[i] <- tmp
	RETURN TRUE
END

