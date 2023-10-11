//
// Created by Jajecnik Marcell on 2023. 05. 05..
//

#include "contracts.h"

void Contract::setCtype(ContractType ctype_in) {
    contract_type = ctype_in;
}

void Contract::setTariff(double tariff_in) {
    tariff = tariff_in;
}

void Contract::setBalance(double balance_in) {
    balance = balance_in;
}

void Contract::addConsumption(double con_in) {
    consumption += con_in;
}

void Contract::setLast_invoicing(Date last_in) {
    last_invoicing = last_in;
}

void Contract::setCtime(Contract_date ctime_in) {
    contract_time = ctime_in;
}

Client* Contract::getClient() {
    return client;
}

size_t Contract::getContractID() const{
    return contract_ID;
}

ContractType Contract::getCtype() const {
    return contract_type;
}

double Contract::getTariff() const {
    return tariff;
}

double Contract::getBalance() const {
    return balance;
}

double Contract::getConsumption() const {
    return consumption;
}

Contract_date Contract::getCtime() const {
    return contract_time;
}

const std::string Contract::Ctype_toString() const {
    switch (contract_type) {
        case ContractType::Regular: return "Regular";
        case ContractType::VIP: return "VIP";
        case ContractType::Premium: return "Premium";
        case ContractType::Corporate: return "Corporate";
        case ContractType::Student: return "Student";
        case ContractType::SeniorCitizen: return "SeniorCitizen";
        case ContractType::Government: return "Government";
        case ContractType::Onetime: return "Onetime";
        default: return "Unknown";
    }
}

Date Contract::getLast_invoicing() const {
    return last_invoicing;
}

void Contract::pay(double amount) {
    balance += amount;
}

void Contract::invoice( const Date &today) {
    std::ofstream outfile;
    std::string filename = client->getName() + "_" + std::to_string(contract_ID) + ".txt";

    outfile.open(filename);
    // Write contract details
    outfile << "Contract details:" << std::endl; 
        outfile<< "Seller details:" << std::endl;
    outfile<<"Seller name: "<< MVM::MVM_company.getsub_Client_info() << std::endl;
    outfile << "Client name: " << getClient()->getName() << std::endl;
    outfile << "Client ID: " << getClient()->getsub_Client_info() << std::endl;
    outfile << "Contract type: " << Ctype_toString() << std::endl;
    outfile << "Contract start date: " << getCtime().getBegin().toString() << std::endl;
    outfile << "Contract end date: " << getCtime().getEnd().toString() << std::endl;
    outfile << "Last invoicing date: " << getLast_invoicing().toString() << std::endl;
    outfile << "Tariff: " << std::fixed << std::setprecision(2) << getTariff() << " Ft/KWh" << std::endl;
    outfile << "Balance: " << std::fixed << std::setprecision(2) << getBalance() << " Ft" << std::endl;
    outfile << "Consumption since last invoicing: " << std::fixed << std::setprecision(2) << getConsumption() << " KWh" << std::endl;

    // Calculate invoice details
    double consumption = getConsumption();
    double prev_balance =getBalance();
    double tariff = getTariff();
    double vat = 0.27; // Value added tax
    double subtotal = consumption * tariff;
    double total = subtotal * (1 + vat);
    double new_balance = prev_balance + total;

    // Write invoice details
    outfile << std::endl;
    outfile << "Invoice details:" << std::endl;
    outfile << "Invoice date: " << today.toString() << std::endl;
    outfile << "Previous balance: " << std::fixed << std::setprecision(2) << prev_balance << " Ft" << std::endl;
    outfile << "Tariff: " << std::fixed << std::setprecision(2) << tariff << " Ft/KWh" << std::endl;
    outfile << "Consumption: " << std::fixed << std::setprecision(2) << consumption << " KWh" << std::endl;
    outfile << "Subtotal: " << std::fixed << std::setprecision(2) << subtotal << " Ft" << std::endl;
    outfile << "VAT (" << std::fixed << std::setprecision(2) << vat*100 << "%): " << std::fixed << std::setprecision(2) << subtotal * vat << " Ft" << std::endl;
    outfile << "Total: " << std::fixed << std::setprecision(2) << total << " Ft" << std::endl;
    outfile << "New balance: " << std::fixed << std::setprecision(2) << new_balance << " Ft" << std::endl;

    outfile.close();
}

Contract::~Contract() {

}