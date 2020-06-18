#pragma once
#include <iostream> 
#include <list> 
#include <iterator> 
#include<vector>
using namespace std;
//Thêm thời gian đợi của mỗi

class Graph
{
    //Thời gian đợi
    int doi_s[20];
    int doi_t[20];
    bool kq = false;
    bool dungct = false;
    int current_s;
    int current_t;


    //số điểm trong đồ thị
    int V;
    int level_s = 0;
    int level_t = 0;

    int cap_s[20];
    int cap_t[20];


    // adj là một mạng mà mỗi phần từ là 1 list
    list<int>* adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    };

    void addEdge(int u, int v)
    {
        this->adj[u].push_back(v);
        this->adj[v].push_back(u);
    };
    //Tính thời gian tại 1 vị trí
    int pathcost(int* parent, int fx[][20], int x)
    {
        int cost = 0;
        int i = x;
        while (parent[i] != -1)
        {
            cost += fx[i][parent[i]];
            i = parent[i];

        }
        return cost;


    }
    
    //lấy vị trí thời gian chờ thấp nhất
    void get(list<int>* queue_s, list<int>* queue_t, int* parent_s, int* parent_t, int fx[][20], bool* visited_s, bool* visited_t)
    {
        if ((queue_s[current_s].size() == 0 && level_s == 0) || (queue_t[current_t].size() == 0 && level_t == 0))
        {
            dungct = true;
            return;
        }
        if (queue_s[current_s].size() != 0 && queue_t[current_t].size() != 0)
        {
            int min = INT_MAX;
            int vitri_s;
            int vitri_t;
            list<int>::iterator i_s;
            list<int>::iterator i_t;

            for (i_s = queue_s[current_s].begin(); i_s != queue_s[current_s].end(); i_s++)
                for (i_t = queue_t[current_t].begin(); i_t != queue_t[current_t].end(); i_t++)
                {
                    if (*i_s == *i_t)
                    {
                        kq = true;
                        visited_s[*i_s] = true;
                        visited_t[*i_t] = true;
                        parent_s[*i_s] = current_s;
                        parent_t[*i_t] = current_t;
                        cap_s[*i_s] = level_s++;
                        cap_t[*i_t] = level_t++;
                        int thu = fx[*i_s][current_s] - fx[*i_t][current_t];
                        if (thu > 0)
                        {
                            doi_t[*i_t] = 0;
                            doi_s[*i_s] = abs(thu);
                        }
                        else if (thu < 0)
                        {
                            doi_t[*i_t] = abs(thu);
                            doi_s[*i_s] = 0;
                        }
                        else
                        {
                            doi_t[*i_t] = 0;
                            doi_s[*i_s] = 0;
                        }
                        return;
                    }
                    if (min > abs(fx[*i_s][current_s] - fx[*i_t][current_t]))
                    {
                        min = abs(fx[*i_s][current_s] - fx[*i_t][current_t]);
                        vitri_s = *i_s;
                        vitri_t = *i_t;
                    }

                }
            queue_s[current_s].remove(vitri_s);
            queue_t[current_t].remove(vitri_t);
            
            int thu = fx[vitri_s][current_s] - fx[vitri_t][current_t];
            if (thu > 0)
            {
                doi_t[vitri_t] = 0;
                doi_s[vitri_s] = abs(thu);
            }
            else if (thu < 0)
            {
                doi_t[vitri_t] = abs(thu);
                doi_s[vitri_s] = 0;
            }
            else
            {
                doi_t[vitri_t] = 0;
                doi_s[vitri_s] = 0;
            }
            parent_s[vitri_s] = current_s;
            parent_t[vitri_t] = current_t;
            current_s = vitri_s;
            current_t = vitri_t;
            visited_s[current_s] = true;
            visited_t[current_t] = true;
            level_s++;
            level_t++;
            cap_s[current_s] = level_s;
            cap_t[current_t] = level_t;
        }
        else if (queue_s[current_s].size() == 0 && queue_t[current_t].size() == 0)
        {
            while (queue_s[current_s].size() == 0)
            {
                visited_s[current_s] = false;
                cap_s[current_s] = 0;
                doi_s[current_s] = 0;
                level_s--;
                queue_s[current_s].clear();
                int a = current_s;
                current_s = parent_s[current_s];
                parent_s[a] = -1;
            }
            while (queue_t[current_t].size() == 0)
            {
                visited_t[current_t] = false;
                cap_t[current_t] = 0;
                doi_t[current_t] = 0;
                level_t--;
                queue_t[current_t].clear();
                int a = current_t;

                current_t = parent_t[current_t];
                parent_t[a] = -1;
            }
            if (level_s > level_t)
            {
                while (level_s != level_t + 1)
                {
                    visited_s[current_s] = false;
                    cap_s[current_s] = 0;
                    doi_s[current_s] = 0;
                    level_s--;
                    queue_s[current_s].clear();

                    int a = current_s;

                    current_s = parent_s[current_s];
                    parent_s[a] = -1;
                }
                queue_s[parent_s[current_s]].push_back(current_s);
                visited_s[current_s] = false;
                cap_s[current_s] = 0;
                doi_s[current_s] = 0;
                level_s--;
                queue_s[current_s].clear();

                int a = current_s;
                current_s = parent_s[current_s];
                parent_s[a] = -1;
            }
            else if (level_s < level_t)
            {
                while (level_t != level_s + 1)
                {
                    visited_t[current_t] = false;
                    cap_t[current_t] = 0;
                    doi_t[current_t] = 0;
                    level_t--;
                    int a = current_t;
                    queue_t[current_t].clear();

                    current_t = parent_t[current_t];
                    parent_t[a] = -1;
                }
                queue_t[parent_t[current_t]].push_back(current_t);
                visited_t[current_t] = false;
                cap_t[current_t] = 0;
                doi_t[current_t] = 0;
                level_t--;
                queue_t[current_t].clear();

                int a = current_t;

                current_t = parent_t[current_t];
                parent_t[a] = -1;
            }

            int min = INT_MAX;
            int vitri_s;
            int vitri_t;


            list<int>::iterator i_s;
            list<int>::iterator i_t;
            for (i_s = queue_s[current_s].begin(); i_s != queue_s[current_s].end(); i_s++)
                for (i_t = queue_t[current_t].begin(); i_t != queue_t[current_t].end(); i_t++)
                {
                    if (*i_s == *i_t)
                    {
                        kq = true;
                        visited_s[*i_s] = true;
                        visited_t[*i_t] = true;
                        parent_s[*i_s] = current_s;
                        parent_t[*i_t] = current_t;
                        cap_s[*i_s] = level_s++;
                        cap_t[*i_t] = level_t++;
                        int thu = fx[*i_s][current_s] - fx[*i_t][current_t];
                        if (thu > 0)
                        {
                            doi_t[*i_t] = 0;
                            doi_s[*i_s] = abs(thu);
                        }
                        else if (thu < 0)
                        {
                            doi_t[*i_t] = abs(thu);
                            doi_s[*i_s] = 0;
                        }
                        else
                        {
                            doi_t[*i_t] = 0;
                            doi_s[*i_s] = 0;
                        }
                        return;
                    }
                        if (min > abs(fx[*i_s][current_s] - fx[*i_t][current_t]) )
                        {
                            min = abs(fx[*i_s][current_s] - fx[*i_t][current_t] );
                            vitri_s = *i_s;
                            vitri_t = *i_t;
                        }
                    
                }
            queue_s[current_s].remove(vitri_s);
            queue_t[current_t].remove(vitri_t);

            int thu = fx[vitri_s][current_s] - fx[vitri_t][current_t];
            if (thu > 0)
            {
                doi_t[vitri_t] = 0;
                doi_s[vitri_s] = abs(thu);
            }
            else if (thu < 0)
            {
                doi_t[vitri_t] = abs(thu);
                doi_s[vitri_s] = 0;
            }
            else
            {
                doi_t[vitri_t] = 0;
                doi_s[vitri_s] = 0;
            }
            parent_s[vitri_s] = current_s;
            parent_t[vitri_t] = current_t;
            current_s = vitri_s;
            current_t = vitri_t;
            visited_s[current_s] = true;
            visited_t[current_t] = true;
            level_s++;
            level_t++;
            cap_s[current_s] = level_s;
            cap_t[current_t] = level_t;


        }
        else if (queue_t[current_t].size()==0)
        {
            
            while (queue_t[current_t].size()==0)
            {
                visited_t[current_t] = false;
                cap_t[current_t] = 0;
                doi_t[current_t] = 0;
                level_t--;
                queue_t[current_t].clear();

                int a = current_t;
                current_t = parent_t[current_t];
                parent_t[a] = -1;
            }
            while (level_s != level_t + 1)
            {
                visited_s[current_s] = false;
                cap_s[current_s] = 0;
                doi_s[current_s] = 0;
                queue_s[current_s].clear();

                level_s--;
                int a = current_s;

                current_s = parent_s[current_s];
                parent_s[a] = -1;
            }
            queue_s[parent_s[current_s]].push_back(current_s);
            visited_s[current_s] = false;
            cap_s[current_s] = 0;
            doi_s[current_s] = 0;
            queue_s[current_s].clear();

            level_s--;
            int a = current_s;

            current_s = parent_s[current_s];
            parent_s[a] = -1;
            int min = INT_MAX;
            int vitri_s;
            int vitri_t;
            
                
                list<int>::iterator i_s;
                list<int>::iterator i_t;
                for (i_s = queue_s[current_s].begin(); i_s != queue_s[current_s].end(); i_s++)
                    for (i_t = queue_t[current_t].begin(); i_t != queue_t[current_t].end(); i_t++)
                    {
                        if (*i_s == *i_t)
                        {
                            kq = true;
                            visited_s[*i_s] = true;
                            visited_t[*i_t] = true;
                            parent_s[*i_s] = current_s;
                            parent_t[*i_t] = current_t;
                            cap_s[*i_s] = level_s++;
                            cap_t[*i_t] = level_t++;
                            int thu = fx[*i_s][current_s] - fx[*i_t][current_t];
                            if (thu > 0)
                            {
                                doi_t[*i_t] = 0;
                                doi_s[*i_s] = abs(thu);
                            }
                            else if (thu < 0)
                            {
                                doi_t[*i_t] = abs(thu);
                                doi_s[*i_s] = 0;
                            }
                            else
                            {
                                doi_t[*i_t] = 0;
                                doi_s[*i_s] = 0;
                            }
                            return;
                        }
                            if (min > abs(fx[*i_s][current_s] - fx[*i_t][current_t]) )
                            {
                                min = abs(fx[*i_s][current_s] - fx[*i_t][current_t] );
                                vitri_s = *i_s;
                                vitri_t = *i_t;
                            }
                        
                    }
                parent_s[vitri_s] = current_s;
                parent_t[vitri_t] = current_t;
                queue_s[current_s].remove(vitri_s);
                queue_t[current_t].remove(vitri_t);

                int thu = fx[vitri_s][current_s] - fx[vitri_t][current_t];
                if (thu > 0)
                {
                    doi_t[vitri_t] = 0;
                    doi_s[vitri_s] = abs(thu);
                }
                else if (thu < 0)
                {
                    doi_t[vitri_t] = abs(thu);
                    doi_s[vitri_s] = 0;
                }
                else
                {
                    doi_t[vitri_t] = 0;
                    doi_s[vitri_s] = 0;
                }
                current_s = vitri_s;
                current_t = vitri_t;
                visited_s[current_s] = true;
                visited_t[current_t] = true;
                level_s++;
                level_t++;
                cap_s[current_s] = level_s;
                cap_t[current_t] = level_t;
            
        }
        else if (queue_s[current_s].size()==0)
        {

            while (queue_s[current_s].size()==0)
            {
                visited_s[current_s] = false;
                cap_s[current_s] = 0;
                doi_s[current_s] = 0;
                queue_s[current_s].clear();

                level_s--;
                int a = current_s;

                current_s = parent_s[current_s];
                parent_s[a] = -1;
            }
            
            while (level_t != level_s + 1)
            {
                visited_t[current_t] = false;
                cap_t[current_t] = 0;
                doi_t[current_t] = 0;
                queue_t[current_t].clear();

                level_t--;
                int a = current_t;

                current_t = parent_t[current_t];
                parent_t[a] = -1;
            }
            queue_t[parent_t[current_t]].push_back(current_t);
            visited_t[current_t] = false;
            cap_t[current_t] = 0;
            doi_t[current_t] = 0;
            queue_t[current_t].clear();

            level_t--;
            int a = current_t;

            current_t = parent_t[current_t];
            parent_t[a] = -1;
            int min = INT_MAX;
            int vitri_s;
            int vitri_t;
            
                
                list<int>::iterator i_s;
                list<int>::iterator i_t;
                for (i_s = queue_s[current_s].begin(); i_s != queue_s[current_s].end(); i_s++)
                    for (i_t = queue_t[current_t].begin(); i_t != queue_t[current_t].end(); i_t++)
                    {
                        if (*i_s == *i_t)
                        {
                            kq = true;
                            visited_s[*i_s] = true;
                            visited_t[*i_t] = true;
                            parent_s[*i_s] = current_s;
                            parent_t[*i_t] = current_t;
                            cap_s[*i_s] = level_s++;
                            cap_t[*i_t] = level_t++;
                            int thu = fx[*i_s][current_s] - fx[*i_t][current_t];
                            if (thu > 0)
                            {
                                doi_t[*i_t] = 0;
                                doi_s[*i_s] = abs(thu);
                            }
                            else if (thu < 0)
                            {
                                doi_t[*i_t] = abs(thu);
                                doi_s[*i_s] = 0;
                            }
                            else
                            {
                                doi_t[*i_t] = 0;
                                doi_s[*i_s] = 0;
                            }
                            return;
                        }

                            if (min > abs(fx[*i_s][current_s] - fx[*i_t][current_t]))
                            {
                                min = abs(fx[*i_s][current_s] - fx[*i_t][current_t])
                                    ;
                                vitri_s = *i_s;
                                vitri_t = *i_t;
                            }

                    }
                parent_s[vitri_s] = current_s;
                parent_t[vitri_t] = current_t;
                queue_s[current_s].remove(vitri_s);
                queue_t[current_t].remove(vitri_t);

                int thu = fx[vitri_s][current_s] - fx[vitri_t][current_t];
                if (thu > 0)
                {
                    doi_t[vitri_t] = 0;
                    doi_s[vitri_s] = abs(thu);
                }
                else if (thu < 0)
                {
                    doi_t[vitri_t] = abs(thu);
                    doi_s[vitri_s] = 0;
                }
                else
                {
                    doi_t[vitri_t] = 0;
                    doi_s[vitri_s] = 0;
                }
                current_s = vitri_s;
                current_t = vitri_t;
                visited_s[current_s] = true;
                visited_t[current_t] = true;
                level_s++;
                level_t++;
                cap_s[current_s] = level_s;
                cap_t[current_t] = level_t;
            
        }
    }
    
    
    //A* cho s
    void bestFirstSearch(list<int>* queue_s, list<int> queue_t[20], int* parent_s, int* parent_t, int fx[][20], bool* visited_s, bool* visited_t)
    {
        if (kq == true)
            return;
        get(queue_s, queue_t, parent_s, parent_t, fx, visited_s, visited_t);
        if (kq == true)
            return;
        if (dungct == true)
            return;
        list<int>::iterator j;
        for (j = adj[current_t].begin(); j != adj[current_t].end(); j++)
        {
            if (!visited_t[*j])
            {
                queue_t[current_t].push_back(*j);
            }
        }
        list<int>::iterator i_s;

        for (i_s = adj[current_s].begin(); i_s != adj[current_s].end(); i_s++)
        {
            if (!visited_s[*i_s])
            {

                queue_s[current_s].push_back(*i_s);
            }
        }
        

    }
    
    void khoitao(list<int>* queue_s, list<int>* queue_t, int* parent_s, int* parent_t, int fx[][20], bool* visited_s, bool* visited_t)
    {
        
        list<int>::iterator i_s;

        for (i_s = adj[current_s].begin(); i_s != adj[current_s].end(); i_s++)
        {
            if (!visited_s[*i_s])
            {

                queue_s[current_s].push_back(*i_s);
            }
        }
        list<int>::iterator i_t;
        for (i_t = adj[current_t].begin(); i_t != adj[current_t].end(); i_t++)
        {
            if (!visited_t[*i_t])
            {
                queue_t[current_t].push_back(*i_t);
            }
        }
    }



    // kiểm tra 2 người đã gặp nhau chưa
    int isIntersecting(bool* visited_s, bool* visited_t, list<int>* queue_s, list<int>* queue_t, int* parent_s, int* parent_t)
    {
        //chạy hết tất cả các đỉnh        
        for (int i = 0; i <20 ; i++)
        {
            //nếu đỉnh đã được cả s và t đi qua
            if (visited_s[i] && visited_t[i] && cap_s[i] == cap_t[i])
                return i;
            else if (visited_s[i] && visited_t[i] )
            {
                if (cap_s[i] != level_s )
                {

                    visited_s[current_s] = false;
                    cap_s[current_s] = 0;
                    doi_s[current_s] = 0;
                    queue_s[current_s].clear();
                    current_s = parent_s[current_s];

                    level_s--;


                    visited_t[current_t] = false;
                    cap_t[current_t] = 0;
                    doi_t[current_t] = 0;
                    queue_t[parent_t[current_t]].push_back(current_t);
                    queue_t[current_t].clear();
                    current_t = parent_t[current_t];
                    level_t--;


                }
                else if (cap_t[i] != level_t )
                {

                    visited_t[current_t] = false;
                    cap_t[current_t] = 0;
                    doi_t[current_t] = 0;
                    queue_t[current_t].clear();
                    current_t = parent_t[current_t];
                    level_t--;


                    visited_s[current_s] = false;
                    cap_s[current_s] = 0;
                    doi_s[current_s] = 0;
                    queue_s[parent_s[current_s]].push_back(current_s);
                    queue_s[current_s].clear();
                    current_s = parent_s[current_s];

                    level_s--;

                }
            }
        }
        return -1;
    };
    int isIntersecting1(bool* visited_s, bool* visited_t, list<int>* queue_s, list<int>* queue_t, int* parent_s, int* parent_t)
    {
        //chạy hết tất cả các đỉnh        
        for (int i = 0; i < 20; i++)
        {
            //nếu đỉnh đã được cả s và t đi qua
            if (visited_s[i] && visited_t[i] && cap_s[i] == cap_t[i])
                return i;
            
        }
        return -1;
    };

    // phương thức in đường đi
    void printPath(int* parent_s, int* parent_t,
        int s, int t, int intersectNode,int fx[][20])
    {
        vector<int> path;
        int wait_s = 0, wait_t = 0;
        path.push_back(intersectNode);
        float time = 0;
        int i = intersectNode;
        while (i != s)
        {
            path.push_back(parent_s[i]);
            wait_s += doi_s[i];
            i = parent_s[i];
        }
        reverse(path.begin(), path.end());
        i = intersectNode;
        while (i != t)
        {
            path.push_back(parent_t[i]);
            wait_t += doi_t[i];
            i = parent_t[i];
        }
        time += (pathcost(parent_s, fx, intersectNode) + pathcost(parent_t, fx, intersectNode) + wait_s + wait_t) / 2;


        vector<int>::iterator it;
        cout << "*****duong di*****\n";
        for (it = path.begin(); it != path.end(); it++)
            cout << *it << " ";
        cout << endl;
        cout << "*****thoi gian doi*****\n";
        cout << "-thoi gian doi cua s la: " << wait_s << endl;
        cout << "-thoi gian doi cua t la: " << wait_t << endl;
        cout << "tong thoi gian de s va t gap nhau la: " << time << endl;
    };

    //  bidirectional searching 
    int biDirSearch(int s, int t, int fx[][20])
    {
        if (s == t)
        {
            kq = true;
        }
        bool visited_s[20], visited_t[20];
        int parent_s[20], parent_t[20];

        // danh sách các thành phố có thể đi
        list<int>* s_queue;
        list<int>* t_queue;
        int intersectNode = -1;

        //Khởi tạo mảng visit
        for (int i = 0; i < V; i++)
        {
            visited_s[i] = false;
            visited_t[i] = false;
        }
        
        //Khởi tạo mảng cấp
        for (int i = 0; i < V; i++)
        {
            cap_s[i] = 0;
            cap_t[i] = 0;
        }
        
        //khởi tạo mảng thời gian đợi
        for (int i = 0; i < 20; i++)
        {
            doi_s[i] = 0;
            doi_t[i] = 0;
        }
        
        // khởi tại parent cho điểm s
        parent_s[s] = -1;
        //Khởi tạo parent cho điểm t
        parent_t[t] = -1;
        current_s = s;
        current_t = t;
        visited_s[current_s] = true;
        visited_t[current_t] = true;
        t_queue = new list<int>[20];

        s_queue = new list<int>[20];
        khoitao(s_queue, t_queue, parent_s, parent_t, fx, visited_s, visited_t);
        int dems;
        int demt;
        do
        {
            

            bestFirstSearch(s_queue,t_queue,parent_s,parent_t,fx,visited_s,visited_t );

            //kiểm tra 2 người có gặp nhau chưa
            intersectNode = isIntersecting(visited_s, visited_t, s_queue, t_queue, parent_s, parent_t);
            if (dungct == true)
                return -1;

            //nếu tìm ra điểm gặp nhau
            if (intersectNode != -1)
            {
                cout << "Tim thay duong di giua " << s << " va "
                    << t << "\n";
                cout << "Gap nhau tai: " << intersectNode << "\n";

                // in ra đường đi và thoát khỏi chương trình
                printPath(parent_s, parent_t, s, t, intersectNode,fx);
                exit(0);
            }
            // }
            dems = 0;
            demt = 0;
            for (int i = 0; i < 20; i++)
            {
                if (s_queue[i].size() == 0)
                    dems++;

            }
            for (int i = 0; i < 20; i++)
                if (t_queue[i].size() == 0)
                    demt++;

        } while (dems != 20 && demt != 20);

        return -1;
    }
    //Nếu không có đường đi thì thực hiện lại với hàm insection khác
    int biDirSearch1(int s, int t, int fx[][20])
    {
        if (biDirSearch(s, t, fx) == -1)
        {
            //
            bool visited_s[20], visited_t[20];
            int parent_s[20], parent_t[20];

            // danh sách các thành phố có thể đi
            list<int>* s_queue;
            list<int>* t_queue;
            int intersectNode = -1;
            kq = false;
            dungct = false;
            //Khởi tạo mảng visit
            for (int i = 0; i < V; i++)
            {
                visited_s[i] = false;
                visited_t[i] = false;
            }

            //Khởi tạo mảng cấp
            for (int i = 0; i < V; i++)
            {
                cap_s[i] = 0;
                cap_t[i] = 0;
            }

            //khởi tạo mảng thời gian đợi
            for (int i = 0; i < 20; i++)
            {
                doi_s[i] = 0;
                doi_t[i] = 0;
            }
            
            // khởi tại parent cho điểm s
            parent_s[s] = -1;
            //Khởi tạo parent cho điểm t
            parent_t[t] = -1;
            current_s = s;
            current_t = t;
            visited_s[current_s] = true;
            visited_t[current_t] = true;
            t_queue = new list<int>[20];

            s_queue = new list<int>[20];
            khoitao(s_queue, t_queue, parent_s, parent_t, fx, visited_s, visited_t);
            do
            {


                bestFirstSearch(s_queue, t_queue, parent_s, parent_t, fx, visited_s, visited_t);

                //kiểm tra 2 người có gặp nhau chưa
                intersectNode = isIntersecting1(visited_s, visited_t, s_queue, t_queue, parent_s, parent_t);
                if (dungct == true)
                    return -1;

                //nếu tìm ra điểm gặp nhau
                if (intersectNode != -1)
                {
                    cout << "Tim thay duong di giua " << s << " va "
                        << t << "\n";
                    cout << "Gap nhau tai: " << intersectNode << "\n";

                    // in ra đường đi và thoát khỏi chương trình
                    printPath(parent_s, parent_t, s, t, intersectNode, fx);
                    exit(0);
                }
                // }

            } while (current_s != -1 && current_t != -1);

            return -1;
        }
    }

};

