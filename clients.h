//
// Created by Jajecnik Marcell on 2023. 05. 04..
//

#ifndef SKELETON_CLIENTS_H
#define SKELETON_CLIENTS_H

#include "date.h"
#include "myvektor.hpp"
#include "contracts.h"
#include <string>

///Elődefiniálás a mycontracts adattag használatához
class Contract;

/**@brief Ügyfél adatait tárolja
 * @param name Az ügyfél neve
 * @param mycontracts Az ügyfél szerződéseit tároló tömb
 * @param SumOfAll_contracts Azt tárolja hogy a kliens megléte alatt összesen hány szerződést kötött (A szerződés azonosítására használ a felhasználó számára)
 */
class Client{
private:
    std::string name;
    MyVector<Contract> mycontracts;
    size_t SumOfAll_contract;

public:
    /**@brief Alapértékes kontruktor
     *
     * @param name_in Ügyfél neve
     * @param sumofContracts A kliens által eddig kötött szerződések száma (nem jelenlegi)
     */
    Client(const std::string name_in):name(std::string(name_in)), SumOfAll_contract(0){}

    /**@brief Visszaadja a kliens által eddig kötött szerződések számát
     *
     * @return kliens által eddig kötött szerződések száma
     */
    size_t getSumOfAll_Contract();

    /**@brief Visszadja a kliens nevét
     *
     * @return kliens neve
     */
    std::string getName() const;

    /**@brief Szerződés hozzáadása a mycontracts hez
     *
     * @param contract_in a hozzáadandó szerződésre mutató referencia.
     */
    void addContract(Contract& contract_in);

    /**
     * @brief Visszaadja a gyermek osztály személyes adatait kiíráshoz egy string-ben.
     * 
     * \return gyermek osztály személyes adatai kiíráshoz egy string-ben
     */
    virtual std::string getsub_Client_info();

    /**
     * @brief Számlát állít ki fájlba.
     * 
     * \param contract_index A szerződés sorszáma a tárolt szerződések között
     */
    void save_invoice(size_t contract_index, const Date& date);

    /**@brief Visszaadja azt a szerződést aminek az azonosítóját megadtuk
     *
     * @param contract_ID A szerződés azonosítója
     * @return
     */
    Contract& getContract(size_t contract_ID);

    /**@brief Virtuális destruktor
     *
     */
    virtual ~Client(){};
};

/**@brief Magánszemély adatait tárolja
 * @param ID A személy személyazonosító száma 8 jegyű
*/
class Person: public Client{
private:
    std::string ID;
public:
    /**@brief Alapértékes konstruktor
     * @param name_in Bejövő magánszemély neve
     * @param ID_in Bejövő magánszemély személyigazolványszáma
     * @param SumOfAll_contract A kliens által eddig kötött szerződések száma (nem jelenlegi)
    */
    Person(const std::string name_in="", std::string ID_in="")
    : Client(std::string(name_in)), ID(ID_in)
    {}

    /**@brief Személyigazolvány beállítása
     *
     * @param ID_in Beérkező személyigazolványszám
     */
    void setID(std::string ID_in);

    /**@brief Magánszemély személyigazolványszámát adja vissza
     *
     * @return Magánszemély személyigazolványszáma
     */
    std::string getID() const;

    /**
     * @brief Visszaadja a gyermek osztály személyes adatait kiíráshoz egy string-ben.
     *
     * \return gyermek osztály személyes adatai kiíráshoz egy string-ben
     */
    std::string getsub_Client_info();

    /**@brief Destruktor
     *
     */
    ~Person();
};

/**@brief Egy cég adatait tárolja
 *@param Tax_ID A cég adóazonosító száma 11 jegyű
 */
class Company: public Client{
private:
    std::string Tax_ID;
public:

    /**@brief Alapértékes kontruktor
     *
     * @param name_in Bejövő Cégnév
     * @param ID_in Bejövő Cég adószám
     * @param SumOfAllContract A kliens által eddig kötött szerződések száma (nem jelenlegi)
     */
    Company(std::string name_in="", std::string ID_in="")
    : Client(name_in), Tax_ID(ID_in)
    {}

    /**@brief Cég adószámának állítása
     *
     * @param ID_in Bejövő Cég adószám
     */
    void setID(std::string ID_in);

    /**@brief Cég adószámát adja vissza
     *
     * @return Cég adószáma
     */
    std::string getID() const;

    /**
     * @brief Visszaadja a gyermek osztály személyes adatait kiíráshoz egy string-ben.
     *
     * \return gyermek osztály személyes adatai kiíráshoz egy string-ben
     */
    std::string getsub_Client_info();

    /**@brief Destruktor
     *
     */
    ~Company();
};

#endif //SKELETON_CLIENTS_H