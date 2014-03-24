/**
 * @opt nodefontcolor "blue"
 * @opt attributes
 * @opt operations
 * @hidden
 */
class UMLOptions {}

/**
 * @opt all
 */
class Person {
    public String Name;
    public String getName();
}

/**
 * @opt shape activeclass
 * @note Active Class
 * @navassoc - - - Goods
 */
class Client extends Person implements Business{
}

interface Business {
    public void buy();
    public void sell(); 
}

/**
 * @opt shape node
 */
class Goods {
}

/**
 * Jimmy
 * @opt shape usecase
 * @opt commentname
 * @note Use Case
 * @depend - <depend> - Goods
 */
class Guest extends Client{}


class Employee extends Person {
}

/**
 * @opt shape collaboration
 * @note
 * String getName() {
 *   return Name;
 * }
 */
class Collaboration extends Person{}

// multiple inherit

/**
 * @extends Client
 */
class Account extends Person{}

/**
 * Business rules
 * @opt shape package
 * @opt commentname
 * @note Package
 */
class Package{}
