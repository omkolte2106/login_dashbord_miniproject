#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <cstdlib>
#include <algorithm>

// Class to parse and store form data
class FormData {
public:
    std::map<std::string, std::string> fields;

    void parse(const std::string& data) {
        std::istringstream ss(data);
        std::string token;

        while (std::getline(ss, token, '&')) {
            auto pos = token.find('=');
            if (pos != std::string::npos) {
                std::string key = token.substr(0, pos);
                std::string value = token.substr(pos + 1);
                std::replace(value.begin(), value.end(), '+', ' '); // decode +
                fields[key] = url_decode(value);
            }
        }
    }

    std::string url_decode(const std::string& str) {
        std::string result;
        char ch;
        int i, ii;
        for (i = 0; i < str.length(); i++) {
            if (int(str[i]) == 37) { // '%'
                sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
                ch = static_cast<char>(ii);
                result += ch;
                i += 2;
            } else {
                result += str[i];
            }
        }
        return result;
    }
};

// Class to validate user login
class LoginSystem {
public:
    bool authenticate(const std::string& username, const std::string& password, const std::string& role) {
        if (role == "teacher" && username == "teacher1" && password == "teach123")
            return true;
        if (role == "student" && username == "student1" && password == "stud123")
            return true;
        if(role=="teacher" && username =="saylimam" && password == "teach123")
            return true; 
        if(role=="student" && username =="om" && password == "11332")
            return true; 
        if(role=="student" && username =="chandu" && password == "11338")
            return true;    
        return false;
    }
};

// Class to generate HTML response
class HTMLRenderer {
public:
    void render(bool success, const std::string& role, const std::string& username) {
        std::cout << "Content-type: text/html\n\n";
        std::cout << "<html><head><title>Login Result</title></head><body>";
        if (success) {
            std::cout << "<h1>Welcome " << role << " " << username << "!</h1>";
        } else {
            std::cout << "<h1>Login Failed</h1><p>Invalid username or password.</p>";
        }
        std::cout << "</body></html>";
    }
};

int main() {
    // Retrieve the content length from the environment
    char* len_str = std::getenv("CONTENT_LENGTH");
    int len = len_str ? std::atoi(len_str) : 0;
    std::string post_data;

    if (len > 0) {
        post_data.resize(len);
        std::cin.read(&post_data[0], len);
    }

    // Parse the form data
    FormData form;
    form.parse(post_data);

    // Get form fields
    std::string username = form.fields["username"];
    std::string password = form.fields["password"];
    std::string role     = form.fields["role"];

    // Authenticate the user
    LoginSystem login;
    bool success = login.authenticate(username, password, role);

    // Generate the HTML response
    HTMLRenderer html;
    html.render(success, role, username);

    return 0;
}
