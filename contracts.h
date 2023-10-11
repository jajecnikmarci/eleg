//
// Created by Jajecnik Marcell on 2023. 05. 05..
//

#ifndef SKELETON_CONTRACTS_H
#define SKELETON_CONTRACTS_H
#include "clients.h"
#include "iomanip"
#include "fstream"
#include "MVM.h"
#include <string>

class Client;

/** @enum ContractType
 * A szerződés fajtáját lehet beállítani vele
 */
enum class ContractType {
    Regular,
    VIP,
    Premium,
    Corporate,
    Student,
    SeniorCitizen,
    Government,
    Onetime
};

/**
 * @class Contract
 * @brief Egy szerződést tárol
 * @param client Tárolja a szerződéstkötő adatait
 * @param contract_ID A szerződés azonosítószáma
 * @param contract_type A szerződés típusát tárolja
 * @param contract_time A szerződés időtartamát adja meg egy kezdő és egy végdátummal
 * @param last_invoicing Utolsó számlakibocsájtás ideje
 * @param tariff A KWh-kénti árat adja meg
 * @param balance Tárolja a szerződéshez tartozó számla egyenlegét
 * @param consumption Tárolja a fogyasztást a legutóbbi számlakibocsájtás óta
 */
class Contract {

public:

    /**@brief Paraméter nélküli konstruktor
     *
     */
    Contract() {};

    /**@brief Alapértékes konstruktor egy szerződéshez
     *
     * @param client_in Szerződést kötő ügyfél (kötelező)
     * @param ctype_in Szerződés típusa
     * @param year_begin Szerződés kezdeti éve
     * @param month_begin Szerződés kezdeti hónapja
     * @param day_begin Szerződés kezdeti napja
     * @param year_end Szerződés végső éve
     * @param month_end Szerződés végső hónapja
     * @param day_end Szerződés végső napja
     * @param invo_in_year Legutóbbi számlázás éve
     * @param invo_in_month Legutóbbi számlázás hónapja
     * @param invo_in_day Legutóbbi számlázás napja
     * @param ContractID_in A szerződés azonosítószáma
     * @param tariff_in KWh-kénti ár
     * @param balance_in Jelenlegi egyenleg
     * @param consumption_in Jelenlegi fogyasztás
     */
    Contract(Client* client_in, ContractType ctype_in, int year_begin, int month_begin, int day_begin, int year_end, int month_end, int day_end, int invo_in_year, int invo_in_month, int invo_in_day, size_t ContractID_in ,double tariff_in=0.0, double balance_in=0.0, double consumption_in=0.0)
            :client(client_in),contract_ID(ContractID_in), contract_type(ctype_in), contract_time(year_begin, month_begin, day_begin, year_end, month_end, day_end), last_invoicing(invo_in_year, invo_in_month, invo_in_day), tariff(tariff_in), balance(balance_in), consumption(consumption_in)
    {}

    // Setter functions
    /**@brief Beállítja a szerződés típusát
     *
     * @param ctype_in Beállítandó szerződéstípus
     */
    void setCtype(ContractType ctype_in);

    /**@brief Beállítja az új tarifát
     *
     * @param tariff_in Beállítandó tarifa
     */
    void setTariff(double tariff_in);

    /**@brief Beállítja a jelenlegi egyenleget
     *
     * @param balance_in Beállítandó egyenleg
     */
    void setBalance(double balance_in);

    /**@brief Hozzáad a fogyasztott mennyiséghez
     *
     * @param con_in Bejövő fogyasztás
     */
    void addConsumption(double con_in);

    /**@brief Beállítja a legutolsó számlázás idejét
     *
     * @param last_in Számlázás időpontja
     */
    void setLast_invoicing(Date last_in);

    /**@brief Beállítja a szerződés időtartományát
     *
     * @param ctime_in Bejövő időtartomány
     */
    void setCtime(Contract_date ctime_in);

    /**@brief Visszaadja az ügyfél adatait
     *
     * @return Ügyfél adatai
     */
    Client* getClient();

    /**@brief Visszaadja a szerződés azonosítóját
     *
     * @return szerződés azonosítója
     */
    size_t getContractID() const;

    /**@brief Visszaadja a szerződés típusát
     *
     * @return Szerződés típusa
     */
   ContractType getCtype() const;

    /**@brief Visszaadja a tarifát
     *
     * @return Jelenlegi tarifa
     */
    double getTariff() const;

    /**@brief Visszaadja a jelenlegi egyenleget
     *
     * @return Jelenlegi egyenleg
     */
    double getBalance() const;

    /**@brief Visszaadja az eddigi fogyasztást a legutóbbi számla kiállítása óta
     *
     * @return Eddigi fogyasztás
     */
    double getConsumption() const;

    /**@brief Visszaadja a szerződés időtartományát
     *
     * @return Szerződés időtartománya
     */
    Contract_date getCtime() const;

    /**@brief A szerződés típusát adja vissza stringként
     *
     * @return szerződés típusa adja vissza stringként
     */
    const std::string Ctype_toString() const;

    /**@brief Visszaadja a legutótóbbi számla kiállításának az időpontját
     *
     * @return Legutótóbbi számla kiállításának az időpontja
     */
    Date getLast_invoicing() const;

    /**@brief Befizetés egyenlegrendezéshez
     *
     * @param amount Befizetett összeg
     */
    void pay(double amount);

    /**@brief Számla kiállítása fájlba
     *
     * @param today számla kiállításának napja (név amiatt mert a számlakiállítás napja általában a jelenlegi nappal egyezik meg)
     */
    void invoice( const Date& today);

    /**@brief Destruktor
     *
     */
    ~Contract();
private:

    Client* client;
    int contract_ID;
    ContractType contract_type;
    Contract_date contract_time;
    Date last_invoicing;
    double tariff;
    double balance;
    double consumption;

};

#endif //SKELETON_CONTRACTS_H
