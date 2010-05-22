/*****************************************************************************
 *                               hashtable-impl.h
 *
 * Implementation for Hashtable class.
 *
 * Zhang Ming, 2009-10
 *****************************************************************************/


/**
 * constructors and destructor
 */
template <typename Object, typename Key>
HashTable<Object, Key>::HashTable( int size ) : tableSize(size)
{
    array = new HashEntry[tableSize];
    if( !array )
    {
        cout << "Out of memory!" << endl << endl;
        exit( 1 );
    }

    makeEmpty();
}

template <typename Object, typename Key>
HashTable<Object, Key>::~HashTable()
{
    delete []array;
}


/**
 * Make the table empty.
 */
template <typename Object, typename Key>
void HashTable<Object, Key>::makeEmpty( )
{
    currentSize = 0;
    for( int i = 0; i < tableSize; ++i )
        array[i].info = EMPTY;
}



/**
 * Searching an element with key "k" and then assign it to "x".
 */
template <typename Object, typename Key>
inline bool HashTable<Object, Key>::search( const Key k, Object &x ) const
{
    int index = findPos( k );

    if( !isActive( index ) )
        return false;
    else
    {
        x = array[index].element;
        return true;
    }
}


/**
 * Inserting an element into the table. If the number of elements
 * is greater than half of the table size, then making "re-hash".
 */
template <typename Object, typename Key>
bool HashTable<Object, Key>::insert( const Object &x )
{
    int currentPos = findPos( x.key );
    if( isActive( currentPos ) )
        return false;

    array[currentPos] = HashEntry( x, ACTIVE );
    if( ++currentSize > tableSize/2 )
        rehash( );

    return true;
}


/**
 * Removing an element with key "k" and then assign it to "x".
 */
template <typename Object, typename Key>
bool HashTable<Object, Key>::remove( const Key k, Object &x )
{
    int currentPos = findPos( k );

    if( !isActive( currentPos ) )
        return false;
    else
    {
        x = array[currentPos].element;
        array[currentPos].info = DELETED;
        currentSize--;
        return true;
    }
}


/**
 * If the current position is active, return true.
 */
template <typename Object, typename Key>
inline bool HashTable<Object, Key>::isActive( int currentPos ) const
{
    return array[currentPos].info == ACTIVE;
}


/**
 * If the current position is active, return true.
 */
template <typename Object, typename Key>
int HashTable<Object, Key>::findPos( const Key k ) const
{
    int offset = 1;
    int currentPos = myhash( k );

    while( array[currentPos].info != EMPTY &&       // these two testing
           array[currentPos].element.key != k )     // cann't be switched
    {
        currentPos += offset;
        offset += 2;
        if( currentPos >= tableSize )
            currentPos -= tableSize;
    }

    return currentPos;
}


/**
 * To ensure the number of elements is not greater than
 * half of the table size.
 */
template <typename Object, typename Key>
void HashTable<Object, Key>::rehash( )
{
    int oldTableSize = tableSize;
    HashEntry *oldArray = array;

    tableSize = nextPrime( 2*oldTableSize );
    array = new HashEntry[tableSize];
    if( !array )
    {
        cerr << "Out of memory!"  << endl << endl;
        exit( 1 );
    }

    for( int j=0; j<tableSize; ++j )
        array[j].info = EMPTY;

    currentSize = 0;
    for( int i=0; i<oldTableSize; ++i )
        if( oldArray[i].info == ACTIVE )
            insert( oldArray[i].element );

    delete []oldArray;
}


/**
 * hash mapping.
 */
template <typename Object, typename Key>
int HashTable<Object, Key>::myhash( const Key k ) const
{
    int hashValue = k % tableSize;
    if( hashValue < 0 )
        hashValue += tableSize;

    return hashValue;
}


/**
 * If "n" is a prime number, return true.
 */
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i=3; i*i<=n; i+=2 )
        if( n%i == 0 )
            return false;

    return true;
}


/**
 * Finding the nest prime number greater than "n".
 */
int nextPrime( int n )
{
    if( n%2 == 0 )
        n++;

    for( ; !isPrime(n); n+=2 )
        ;

    return n;
}
