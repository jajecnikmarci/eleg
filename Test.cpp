#include <iostream>

#include "memtrace.h"
#include "MVM.h"
Company MVM::MVM_company = Company("Meseorszagi Villamos Muvek ZRT.", "10760798244");
int MVM::save_version = 0;

#include "gtest_lite.h"

/**@brief Teszt makro vezerli a vegrehajtando tesztesetek szamat.
 * TST 1: MyVektor
 * TST 2: Date
 * TST 3: Contract_date
 * TST 4: Client
 * TST 5: Person
 * TST 6: Company
 * TST 7: Contract
 * TST 8: MVM
 * TST 9: Fajlkezeles
 */
#define TST 9



#define MEMTRACE_H

int main() {
    
#if TST > 0

        TEST(MyVector, tesztek) {

            MyVector<int> int_test;
            MyVector<double> double_test;
            EXPECT_EQ(10, int_test.capacity()); // Alapertelmezett ertek
            EXPECT_EQ(0, int_test.size());
            int_test.push_back(1);
            EXPECT_EQ(1, int_test.size());
            int_test.pop_back();
            EXPECT_EQ(0, int_test.size());
            int_test.pop_back(); //Torles ha nincs semmi bajt okoz-e?

            for (size_t i = 0; i < 11; ++i) {
                int_test.push_back(i);
                double_test.push_back(i);
            }
            EXPECT_EQ(20, int_test.capacity());
            EXPECT_EQ(11, int_test.size());

            for (size_t i = 0; i < 11; ++i) {
                int_test.erase(0);
                double_test.pop_back();
            }

            EXPECT_EQ(0, int_test.size());
            EXPECT_EQ(0, double_test.size());

            for (size_t i = 0; i < 5; ++i) {
                int_test.push_back(i);
            }
            for (size_t i = 0; i < 5; i++)
            {
                EXPECT_EQ(i, int_test[i]);
            }
            EXPECT_THROW(int_test[-1], std::range_error);
            EXPECT_THROW(int_test[5], std::range_error);

        } END
#endif

#if TST > 1

            TEST(Date, tesztek) {

            Date a(2023, 05, 14);
            EXPECT_TRUE(std::string("2023-05-14") == a.toString());
            EXPECT_THROW(Date b(1700, 05, 14), std::range_error);
            EXPECT_THROW(Date c(2000, 0, 14), std::range_error);
            Date b(2000, 1, 14);
            Date c(2000, 1, 14);
            EXPECT_TRUE(b == c);
            Date d(2000, 2, 14);
            Date e(2000, 3, 14);
            EXPECT_FALSE(d == e);
            EXPECT_TRUE(d > b);
            EXPECT_TRUE(b <= d);
            EXPECT_TRUE(d >= b);
            e.print_date();

            std::cout << " = " << e<< std::endl;
        }END

#endif

#if TST > 2

            TEST(Contract_date, tesztek) {

            Date a(2000, 3, 14);
            Contract_date c(2000, 3, 14, 2222, 03, 12);
            EXPECT_TRUE(a == c.getBegin());
            Date b(2222, 03, 12);
            Contract_date d(2000, 3, 14, 2222, 03, 12);
            EXPECT_TRUE(b == d.getEnd());
            c.setBegin(2222, 03, 12);
            EXPECT_TRUE(b == c.getBegin());
            d.setEnd(2000, 3, 14);
            EXPECT_TRUE(a == d.getEnd());
            c.setBegin(a);
            EXPECT_TRUE(a == c.getBegin());
            Date i(2230, 03, 02);
            c.setEnd(i);
            EXPECT_TRUE(i == c.getEnd());
            EXPECT_THROW(Contract_date e(2250, 3, 14, 2222, 03, 12), std::range_error);
            Contract_date f(2000, 3, 14, 2222, 03, 12);
            Date g(2000, 3, 15);
            EXPECT_TRUE(f.contains(g));
            Contract_date h(2020, 3, 14, 2202, 03, 12);
            f = h;
            EXPECT_TRUE(Date(2020, 3, 14) == f.getBegin());
            EXPECT_TRUE(Date(2202, 03, 12) == f.getEnd());
            EXPECT_THROW(f.setBegin(2222, 03, 12), std::range_error);
            EXPECT_THROW(f.setEnd(2000, 03, 12), std::range_error);
            EXPECT_THROW(f.setBegin(Date(2222, 03, 12)), std::range_error);
            EXPECT_THROW(f.setEnd(Date(2000, 03, 12)), std::range_error);

        }END

#endif

#if TST > 3

            TEST(Client, tesztek) {

            Client* a = new Client("En");
            EXPECT_EQ(0, a->getSumOfAll_Contract());
            EXPECT_TRUE(std::string("En") == a->getName());
            Contract b(a, ContractType::Regular, 2000, 03, 11, 2004, 03, 12, 2003, 12, 22, a->getSumOfAll_Contract() + 1, 74);
            a->addContract(b);
            EXPECT_EQ(1, a->getSumOfAll_Contract());
            EXPECT_EQ(1, a->getContract(1).getContractID());
            EXPECT_TRUE(std::string("Client name: En") == a->getsub_Client_info());
            EXPECT_THROW(a->getContract(0), std::range_error);
            delete a;

        }END

#endif

#if TST > 4

            TEST(Person, tesztek) {
            Person a("En", "167890ke");
            EXPECT_STREQ("167890ke", a.getID().c_str());
            EXPECT_TRUE("Person name: En, ID: 167890ke" == a.getsub_Client_info());
            a.setID("123132al");
            EXPECT_TRUE(a.getID() == "123132al");
        }END

#endif

#if TST > 5

            TEST(Company, tesztek) {

            Company a("En", "16789034647");
            EXPECT_STREQ("16789034647", a.getID().c_str());
            EXPECT_STREQ("Company name: En, Tax ID: 16789034647", a.getsub_Client_info().c_str());
            a.setID("12313212345");
            EXPECT_TRUE(a.getID() == "12313212345");
        }END

#endif

#if TST > 6

            TEST(Contract, tesztek) {

            Client* a = new Client("En");
            Contract b(a, ContractType::Regular, 2000, 03, 11, 2004, 03, 12, 2003, 12, 22, a->getSumOfAll_Contract() + 1, 74);
            b.setCtype(ContractType::VIP);
            EXPECT_TRUE(ContractType::VIP == b.getCtype());
            EXPECT_STREQ("VIP", b.Ctype_toString().c_str());
            b.setTariff(84);
            EXPECT_EQ(84, b.getTariff());
            b.addConsumption(55);
            EXPECT_EQ(55, b.getConsumption());
            b.setBalance(-66);
            EXPECT_EQ(-66, b.getBalance());
            b.pay(66);
            EXPECT_EQ(0, b.getBalance());
            EXPECT_TRUE(Date(2003, 12, 22) == b.getLast_invoicing());
            b.setLast_invoicing(Date(2000, 03, 11));
            EXPECT_TRUE(Date(2000, 03, 11) == b.getLast_invoicing());
            EXPECT_TRUE(a->getName() == b.getClient()->getName());
            Contract_date c(2000, 3, 14, 2222, 03, 12);
            b.setCtime(c);
            EXPECT_TRUE(b.getCtime().getBegin() == c.getBegin() && b.getCtime().getEnd() == c.getEnd());
            EXPECT_EQ(1, b.getContractID());
            delete a;///Mivel nem lett létrehozva a főosztály ami ezt felszabadítaná

        }END

#endif

#if TST > 7

            TEST(MVM, tesztek) {

            MVM mvm;
            Person* a = new Person("En", "198245uf");
            mvm.addClient(a);
            EXPECT_TRUE(a == mvm.getClient("En", "198245uf"));
            mvm.addContract(a, ContractType::Regular, 2000, 03, 11, 2004, 03, 12, 2003, 12, 22);
            EXPECT_EQ(a->getSumOfAll_Contract(), mvm.getClient("En", "198245uf")->getContract(1).getContractID());
            EXPECT_STREQ("Company name: Meseorszagi Villamos Muvek ZRT., Tax ID: 10760798244", mvm.getCompanyDetails().c_str());
        }END

#endif

#if TST > 8


            MVM mvm;
        TEST(Fajlkezeles, szamlazas) {
            Person* a = new Person("En", "1982451");
            mvm.addClient(a);
            mvm.addContract(a, ContractType::Regular, 2000, 03, 11, 2004, 03, 12, 2003, 12, 22);
            a->save_invoice(1, Date(2004, 02, 14));
        }END
            TEST(Fajlkezeles, load_from_console) {
            for (size_t i = 0; i < 5; i++)
            {
                mvm.load_from_console();
            }
            EXPECT_THROW(mvm.load_from_console(), std::invalid_argument);///Hibás bemenet adása
            
        } END
            TEST(Fajlkezeles, save) {
            EXPECT_NO_THROW(mvm.save());
        } END
            TEST(Fajlkezeles, load_from_file) {
            MVM mvm2;
            EXPECT_THROW(mvm2.load_from_save(10), std::ios_base::failure);///Nem létező mentés
            EXPECT_NO_THROW(mvm2.load_from_save(1));
            EXPECT_THROW(mvm2.load_from_save(0), std::invalid_argument);
        } END


#endif


    return 0;
    
}
