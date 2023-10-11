//
// Created by Jajecnik Marcell on 2023. 05. 04..
//

#include "MVM.h"

//Company MVM::MVM_company = Company("Meseorszagi Villamos Muvek ZRT.", "10760798244");
//int MVM::save_version = 0;

void MVM::addClient(Client* client_in) {
    clients.push_back(client_in);
}

void MVM::addContract(Client* client_in, ContractType ctype_in, int year_begin, int month_begin, int day_begin, int year_end, int month_end, int day_end, int invo_in_year, int invo_in_month, int invo_in_day, double tariff_in, double balance_in, double consumption_in) {
    Contract new_contract(client_in, ctype_in, year_begin, month_begin, day_begin, year_end, month_end, day_end, invo_in_year, invo_in_month, invo_in_day, (client_in->getSumOfAll_Contract() + 1), tariff_in, balance_in, consumption_in);
    client_in->addContract(new_contract);
}

Client *MVM::getClient(const std::string name_in, const std::string somekindofID) {
    for (size_t i = 0; i < clients.size(); ++i) {
        std::string subclient_info = clients[i]->getsub_Client_info();
        if (name_in == clients[i]->getName() &&
            ((subclient_info.substr(subclient_info.length() - 11, 11) == somekindofID ||
                subclient_info.substr(subclient_info.length() - 8, 8) == somekindofID)))
        return clients[i];
    }
    return nullptr;
}

const std::string MVM::getCompanyDetails() {
    return MVM_company.getsub_Client_info();
}

void MVM::deleteClient(const std::string name_in, const std::string somekindofID) {
    delete getClient(name_in, somekindofID);
}

void MVM::save() {
    save_version++;
    std::string filename = "save_" + std::to_string(save_version) + ".txt";
    std::ofstream outputFile;  // Open the file for writing
    outputFile.open(filename, std::ios::out);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        throw std::ios_base::failure("Error opening file for writing: " + filename);
    }
    size_t client_number = clients.size();
    for (size_t i = 0; i < client_number; i++)
    {
        
        size_t contract_number = clients[i]->getSumOfAll_Contract();
        for (size_t j = 1; j <= contract_number; j++)
        {
            Contract contract_out;
            try {
                contract_out = clients[i]->getContract(j); // Throws exception when contract is invalid
            }
            catch (const std::range_error& e) {
                continue;
            }
                
            outputFile << contract_out.getClient()->getName() << std::endl;
            outputFile << contract_out.getClient()->getsub_Client_info() << std::endl;
            outputFile << contract_out.getContractID() << std::endl;
            outputFile << contract_out.Ctype_toString() << std::endl;
            outputFile << contract_out.getCtime().getBegin().toString() << std::endl;
            outputFile << contract_out.getCtime().getEnd().toString() << std::endl;
            outputFile << contract_out.getLast_invoicing().toString() << std::endl;
            outputFile << std::fixed << std::setprecision(2) << contract_out.getTariff()  << std::endl;
            outputFile << std::fixed << std::setprecision(2) << contract_out.getBalance() << std::endl;
            outputFile << std::fixed << std::setprecision(2) << contract_out.getConsumption()  << std::endl;
        }

    }
    outputFile.close();
}

bool MVM::is_all_number(const std::string& str_in) {
    for (size_t i = 0; i < str_in.length(); i++)
    {
        if (!std::isdigit(str_in[i])) return false;
    }
    return true;
}

bool MVM::is_string_double(std::string& str_in) {
    size_t str_len = str_in.length();
    size_t i = 0;
    while (i<str_len&&str_in[i]!='.')
    {
        if (!std::isdigit(str_in[i])) return false;
        i++;
    }
    i++;
    while (i < str_len)
    {
        if (!std::isdigit(str_in[i])) return false;
        i++;
    };
    
    return true;
}

ContractType MVM::Ctype_fromString(const std::string contract_type) {
    if (contract_type == std::string("Regular"))             return ContractType::Regular;
    if (contract_type == std::string("VIP"))                 return ContractType::VIP;
    if (contract_type == std::string("Premium"))             return ContractType::Premium;
    if (contract_type == std::string("Corporate"))           return ContractType::Corporate;
    if (contract_type == std::string("Student"))             return ContractType::Student;
    if (contract_type == std::string("SeniorCitizen"))       return ContractType::SeniorCitizen;
    if (contract_type == std::string("Government"))          return ContractType::Government;
    if (contract_type == std::string("Onetime"))             return ContractType::Onetime;
    throw std::invalid_argument("Nem letezo szerzodes tipus");
    return ContractType::Onetime;
}

void MVM::load_from_stream(std::istream& is) {
    std::string name_in, sub_client_info_in, contract_ID_in, ctype_in, begin, end_in,  last_invoicing_in, tariff_in, balance_in, consumption_in;
    if (
        !std::getline(is, name_in)) throw std::out_of_range("End of file");
    std::getline(is, sub_client_info_in);
    if (&is != &std::cin) std::getline(is, contract_ID_in); ///Csak ha fájlból olvasunk
    std::getline(is, ctype_in);
    std::getline(is, begin);
    std::getline(is, end_in);
    std::getline(is, last_invoicing_in);
    std::getline(is, tariff_in);
    std::getline(is, balance_in);
    std::getline(is, consumption_in);

    Client* client_in;
    if (sub_client_info_in.substr(0, 6) == "Person") {
        client_in = getClient(name_in, sub_client_info_in.substr(sub_client_info_in.length() - 8, 8));
        if (client_in == nullptr) {
            client_in = new Person(name_in, sub_client_info_in.substr(sub_client_info_in.length() - 8, 8));
            addClient(client_in);
        }
    }
    else if(sub_client_info_in.substr(0, 7) == "Company"){
        client_in = getClient(name_in, sub_client_info_in.substr(sub_client_info_in.length() - 11, 11));
        if (client_in == nullptr) {
            client_in = new Company(name_in, sub_client_info_in.substr(sub_client_info_in.length() - 11, 11));
            addClient(client_in);
        }
    }
    else
    {
        throw std::invalid_argument("Rossz bejovo adat");
    }

    if (
        begin.length() != 10  ||
        end_in.length() != 10 ||
        last_invoicing_in.length() != 10 ||
        !is_all_number(begin.substr(0, 4)) ||
        !is_all_number(begin.substr(5, 2)) ||
        !is_all_number(begin.substr(8, 2)) ||
        !is_all_number(end_in.substr(0, 4)) ||
        !is_all_number(end_in.substr(5, 2)) ||
        !is_all_number(end_in.substr(8, 2)) ||
        !is_all_number(last_invoicing_in.substr(0, 4)) ||
        !is_all_number(last_invoicing_in.substr(5, 2)) ||
        !is_all_number(last_invoicing_in.substr(8, 2)) ||
        !is_string_double(tariff_in) || ///
        !is_string_double(balance_in) ||///
        !is_string_double(consumption_in)///
        )
        throw std::invalid_argument("Rossz bejovo adat");

    //Conversion
    int year_begin, month_begin, day_begin, year_end, month_end, day_end, invo_in_year, invo_in_month, invo_in_day;

    year_begin = std::stoi(begin.substr(0, 4));
    month_begin = std::stoi(begin.substr(5, 2));
    day_begin = std::stoi(begin.substr(8, 2));
    year_end = std::stoi(end_in.substr(0, 4));
    month_end = std::stoi(end_in.substr(5, 2));
    day_end = std::stoi(end_in.substr(8, 2));
    invo_in_year = std::stoi(last_invoicing_in.substr(0, 4));
    invo_in_month = std::stoi(last_invoicing_in.substr(5, 2));
    invo_in_day = std::stoi(last_invoicing_in.substr(8, 2));

    


    ContractType contract_type_in = Ctype_fromString(ctype_in);

    double tariffin, balancein, consumptionin;
    tariffin = std::stod(tariff_in);
    balancein = std::stod(balance_in);
    consumptionin = std::stod(consumption_in);
    
    if (&is != &std::cin) {
        size_t contractIDin = stoi(contract_ID_in);
        Contract contract_in(
            client_in,
            contract_type_in,
            year_begin,
            month_begin,
            day_begin,
            year_end,
            month_end,
            day_end,
            invo_in_year,
            invo_in_month,
            invo_in_day,
            contractIDin,
            tariffin,
            balancein,
            consumptionin
        );
        client_in->addContract(contract_in);
        
    }
    else
    {
        addContract(client_in,
            contract_type_in,
            year_begin,
            month_begin,
            day_begin,
            year_end,
            month_end,
            day_end,
            invo_in_year,
            invo_in_month,
            invo_in_day,
            tariffin,
            balancein,
            consumptionin);
    }

    
    
};

void MVM::load_from_save(int version_id_in) {
    std::string filename = "save_" + std::to_string(version_id_in) + ".txt";
    std::ifstream inputFile;  
    inputFile.open(filename, std::ios::in);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        inputFile.close();
        throw std::ios_base::failure("Error opening file for reading: " + filename);
    }
    while (inputFile)
    {
        try {
            load_from_stream(inputFile);
        }
        catch (std::invalid_argument ia) {
            std::cerr << "Invalid argument: " << ia.what() << '\n';
            inputFile.close();
            throw std::invalid_argument("Rossz forrasfajl");
        }
        catch (std::out_of_range end) { break; }
    }
    inputFile.close();
}

void MVM::load_from_console() {
    std::cout << "Kerem adja meg a szerzodés adatait az alabbi minta alapjan:" << std::endl;
    std::cout<<"Nev" << std::endl;
    std::cout<< "Ugyfel tipusa es azonositoja (Person/Company, ceg eseten az adoazonosito 11 jegyu, maganszemely szemelyigazolvanyszama 8 kerekteru)" << std::endl;
    std::cout<< "Szerzodes tipusa: (Regular/VIP/Premium/Corporate/Student/SeniorCitizen/Government/Onetime)" << std::endl;
    std::cout<<"Szerzodes kezdete: (pl.: 2004-03-11)" << std::endl;
    std::cout<< "Szerzodes vege: (pl.: 2004-03-11)" << std::endl;
    std::cout<<"Legutobbi szamlazas napja: (pl.: 2004-03-11) ha meg nem volt a szerzodes kezdetének napja" << std::endl;
    std::cout<< "Tarifa erteke (kw/h-ban megadva, mertekegyseg nelkul)" << std::endl;
    std::cout<<"Egyenleg erteke (Ft-ban megadva, mertekegyseg nelkul)" << std::endl;
    std::cout<<"Fogyasztas erteke (kw/h-ban megadva, mertekegyseg nelkul)" << std::endl;
    try {
        load_from_stream(std::cin);
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
            throw std::invalid_argument("Rosszul megadott adat(ok)");
    }
    std::cout << "Bevitel sikeres!" << std::endl;
}

MVM::~MVM(){
    for (size_t i = 0; i < clients.size(); i++)
    {
        delete clients[i];
    }
}
