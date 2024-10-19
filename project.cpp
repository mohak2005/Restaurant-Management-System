#include <iostream>
#include <string>
using namespace std;

class MenuItem {
private:
    string name;
    double price;
    string category;

public:
    MenuItem() {}

    MenuItem(string itemName, double itemPrice, string itemCategory) {
        name = itemName;
        price = itemPrice;
        category = itemCategory;
    }

    void displayItem() const {
        cout << name << "- Rs." << price << " (" << category << ")" << endl;
    }

    string getName() const { return name; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }
};

class Table {
    int tableId;
    bool isReserved;

public:
    Table(int id) : tableId(id), isReserved(false) {}

    void reserveTable() {
        isReserved = true;
    }

    void displayTable() {
        cout << "Table ID: " << tableId << ", Reserved: " << (isReserved ? "Yes" : "No") << endl;
    }
};

class Order {
    MenuItem items[10];
    int itemCount;
    double totalPrice;

public:
    Order() : itemCount(0), totalPrice(0.0) {}

    void addItem(const MenuItem &item) {
        if (itemCount < 10) {
            items[itemCount] = item;
            totalPrice += item.getPrice();
            itemCount++;
        } else {
            cout << "Order is full, cannot add more items." << endl;
        }
    }

    void removeItem(int index) {
        if (index >= 0 && index < itemCount) {
            totalPrice -= items[index].getPrice();
            for (int i = index; i < itemCount - 1; i++) {
                items[i] = items[i + 1];
            }
            itemCount--;
        } else {
            cout << "Invalid item index!" << endl;
        }
    }

    void displayOrder() const {
        cout << "Order Details:" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << i + 1 << ". ";
            items[i].displayItem();
        }
        cout << "Total Price: ₹" << totalPrice << endl;
    }

    double getTotalPrice() const { return totalPrice; }
};

class Customer {
private:
    string name;
    string phoneNumber;
    Order order;

    bool isValidPhoneNumber(const string &phone) const {
        if (phone.length() != 10) {
            return false;
        }
        for (char c : phone) {
            if (!isdigit(c)) {
                return false;
            }
        }
        return true;
    }

public:
    Customer(string customerName, string customerPhone) : name(customerName) {
        while (!isValidPhoneNumber(customerPhone)) {
            cout << "Invalid phone number. Please enter a 10-digit phone number: ";
            cin >> customerPhone;
        }
        phoneNumber = customerPhone;
    }

    void placeOrder(const MenuItem &item) {
        order.addItem(item);
    }

    void viewOrder() const {
        cout << "Customer: " << name << " (Phone: " << phoneNumber << ")" << endl;
        order.displayOrder();
    }

    void cancelOrder() {
        order = Order(); // Reset the order
        cout << "Order canceled." << endl;
    }
};

class Restaurant {
private:
    MenuItem menu[10];
    int menuItemCount;

public:
    Restaurant() : menuItemCount(0) {}

    void addMenuItem(const MenuItem &item) {
        if (menuItemCount < 20) {
            menu[menuItemCount] = item;
            menuItemCount++;
        } else {
            cout << "Menu is full, cannot add more items." << endl;
        }
    }

    void removeMenuItem(int index) {
        if (index >= 0 && index < menuItemCount) {
            for (int i = index; i < menuItemCount - 1; i++) {
                menu[i] = menu[i + 1];
            }
            menuItemCount--;
            cout << "Menu item removed." << endl;
        } else {
            cout << "Invalid menu item index!" << endl;
        }
    }

    void displayMenu() const {
        cout << "Menu:" << endl;
        for (int i = 0; i < menuItemCount; i++) {
            cout << i + 1 << ". ";
            menu[i].displayItem();
        }
    }

    MenuItem getMenuItem(int index) const {
        if (index >= 0 && index < menuItemCount) {
            return menu[index];
        } else {
            cout << "Invalid menu item index" << endl;
            return MenuItem();
        }
    }
};

int main() {
    Restaurant restaurant;

    restaurant.addMenuItem(MenuItem("Pizza", 200, "Main Course"));
    restaurant.addMenuItem(MenuItem("Burger", 130, "Main Course"));
    restaurant.addMenuItem(MenuItem("Shahi Paneer (with Naan)", 300, "Main Course"));
    restaurant.addMenuItem(MenuItem("Dal Makhni (with Naan)", 270, "Main Course"));
    restaurant.addMenuItem(MenuItem("Kadai Paneer (with Naan)", 300, "Main Course"));
    restaurant.addMenuItem(MenuItem("Soya Chaap", 230, "Main Course"));
    restaurant.addMenuItem(MenuItem("Veg Biryani", 300, "Main Course"));
    restaurant.addMenuItem(MenuItem("Chowmein", 110, "Main Course"));
    restaurant.addMenuItem(MenuItem("Spring Rolls", 90, "Main Course"));
    restaurant.addMenuItem(MenuItem("Coke", 30, "Beverages"));

    string customerName;
    string customerPhone;

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter your phone number: ";
    cin >> customerPhone;
    cout<<"____________________________________"<<endl;

    Customer customer(customerName, customerPhone);

    Table table1(1); 

    cout << "************Welcome to the Restaurant!*************" << endl;
    int choice;
    do {
        cout << "\n1. Display Menu\n2. Book Table\n3. Place Order\n4. View Order\n5. Cancel Order\n6. Add items in your Menu List\n7. Remove Menu Item\n8. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            restaurant.displayMenu();
            break;

        case 2:
            table1.reserveTable();
            table1.displayTable();
            break;

        case 3: {
            int itemIndex;
            restaurant.displayMenu();
            cout << "Enter the menu item number to add to your order: ";
            cin >> itemIndex;

            MenuItem item = restaurant.getMenuItem(itemIndex - 1);
            if (!item.getName().empty()) {
                customer.placeOrder(item);
                cout << item.getName() << " added to your order." << endl;
            }
            break;
        }

        case 4:
            customer.viewOrder();
            break;

        case 5:
            customer.cancelOrder();
            break;

        case 6: {
            string name, category;
            double price;
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter item price: ";
            cin >> price;
            cout << "Enter item category: ";
            cin.ignore();
            getline(cin, category);
            restaurant.addMenuItem(MenuItem(name, price, category));
            
        }

        case 7: {
            int itemIndex;
            restaurant.displayMenu();
            cout << "Enter the menu item number to remove: ";
            cin >> itemIndex;
            restaurant.removeMenuItem(itemIndex - 1);
            break;
        }

        case 8:
            cout << "Thank you for visiting!" << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
