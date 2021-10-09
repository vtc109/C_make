#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "weightedGraphlib.h"
#include "jrb.h"
#include "jval.h"
#include "dllist.h"
#include "fields.h"
#define INFINITIVE_VALUE 10000000
double shortestPath(Graph graph, int start, int stop, int *path, int *length)
{
    double total, distance[10000];
    int min, id, i, n, neighbor, position, previous[10000], output[10000], temp[10000];
    Dllist queue, shortest, node;

    for (i = 0; i < 10000; i++)
    {
        distance[i] = INFINITIVE_VALUE;
    }

    distance[start] = 0;
    previous[start] = start;

    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while (!dll_empty(queue))
    {

        min = INFINITIVE_VALUE;

        dll_traverse(node, queue)
        {
            id = jval_i(node->val);
            if (min > distance[id])
            {
                min = distance[id];
                shortest = node;
            }
        }

        id = jval_i(shortest->val);
        dll_delete_node(shortest);

        if (id == stop)
            break;

        n = outdegree(graph, id, output);
        for (i = 0; i < n; i++)
        {
            neighbor = output[i];
            if (distance[neighbor] > distance[id] + getEdgeValue(graph, id, neighbor))
            {
                distance[neighbor] = distance[id] + getEdgeValue(graph, id, neighbor);
                previous[neighbor] = id;
                dll_append(queue, new_jval_i(neighbor));
            }
        }
    }

    total = distance[stop];
    if (total != INFINITIVE_VALUE)
    {
        temp[0] = stop;
        position = 1;
        while (stop != start)
        {
            stop = previous[stop];
            temp[position] = stop;
            position += 1;
        }
        for (i = position - 1; i >= 0; i--)
        {
            path[position - i - 1] = temp[i];
        }
        *length = position;
    }

    return total;
}
int main()
{
    int menu;
    Graph g = createGraph();
    IS is1, is2;
    JRB ptr;
    int id1, id2;
    int id;
    char *str = (char *)malloc(250 * sizeof(char));
    if (!str)
    {
        printf("\nMemory Error");
        exit(0);
    }
    int max = 0, temp1, temp2, temp3, min = INFINITIVE_VALUE;
    int indeg[10000], outdeg[10000];
    int indeg1[10000], outdeg1[10000];
    int count1, count2;
    double page_rank[10000], page_rank_temp[10000];
    int tmp1, tmp2;
    for (int i = 0; i < 10000; i++)
    {
        page_rank[i] = 1;
        page_rank_temp[i] = -1;
    }
    int output1[10000], output2[10000];
    while (1)
    {
        printf("\n---MENU---");
        printf("\n1.DOC FILE VA GHI RA MAN HINH");
        printf("\n2.PAGE RANK");
        printf("\n3.PAGE RANK M LAN");
        printf("\n4.THONG TIN WEBPAGE");
        printf("\n5.KHOANG CACH NHO NHAT GIUA 2 PAGE");
        printf("\n6.Exit");
        do
        {
            printf("\nChon menu (1-6):");
            scanf("%d", &menu);
        } while (menu < 1 || menu > 6);
        switch (menu)
        {
        case 1:
            printf("\n---Menu 1---");
            is1 = new_inputstruct("webpages.txt");
            is1->
            while (get_line(is1) >= 0)
            {
                if (is1->NF == 1)
                {
                    printf("\nSo luong Webpages la: %d", atoi(is1->fields[0]));
                }
                else if (is1->NF == 2)
                {
                    id = atoi(is1->fields[1]);
                    str = strdup(is1->fields[0]);
                    printf("\n%-s\t%-d", str, id);
                    addVertex(g, id, str);
                }
            }
            jettison_inputstruct(is1);
            is2 = new_inputstruct("pageConnections.txt");
            double w = 1;
            while (get_line(is2) >= 0)
            {
                if (is2->NF > 1)
                {
                    id1 = atoi(is2->fields[0]);
                    for (int i = 1; i < is2->NF; i++)
                    {
                        id2 = atoi(is2->fields[i]);
                        addEdge(g, id1, id2, w);
                    }
                }
            }
            jettison_inputstruct(is2);
            
        
        
        //todo: Indeg & Outdeg
            jrb_traverse(ptr, g->vertices)
            {
                temp1 = jval_i(ptr->key);
                temp2 = indegree(g, temp1, indeg);
                if (temp2 > max)
                {
                    max = temp2;
                }
            }
            printf ("\n");
            printf("\n Cac canh co lien ket vao lon nhat voi %d lien ket la:", max);
            jrb_traverse(ptr, g->vertices)
            {
                temp1 = jval_i(ptr->key);
                temp2 = indegree(g, temp1, indeg);
                if (temp2 == max)
                {
                    printf(" %d", temp1);
                }
            }
            jrb_traverse(ptr, g->vertices)
            {
                temp1 = jval_i(ptr->key);
                temp2 = indegree(g, temp1, indeg);
                if (temp2 < min)
                {
                    min = temp2;
                }
            }
            printf("\n Cac canh co lien ket vao be nhat voi %d lien ket la:", min);
            jrb_traverse(ptr, g->vertices)
            {
                temp1 = jval_i(ptr->key);
                temp2 = indegree(g, temp1, indeg);
                if (temp2 == min)
                {
                    printf(" %-5d", temp1);
                }
            }
            break;
        case 2:
            printf("---Menu 2---");
            //Khoi tao page_rank cua cac dinh//
            for (int i = 0; i < 10000; i++)
            {
                if (getVertex(g, i) != NULL)
                {
                    temp1 = indegree(g, i, output1);
                    page_rank_temp[i] = 0;
                    for (int j = 0; j < temp1; j++)
                    {
                        temp2 = outdegree(g, output1[j], output2);
                        page_rank_temp[i] += (double)(page_rank[output1[j]] / temp2);
                    }
                }
            }
            for (int i = 0; i < 10000; i++)
            {
                if (page_rank_temp[i] > 0)
                    page_rank[i] = page_rank_temp[i];
            }
            for (int i = 0; i < 10000; i++)
            {
                if (getVertex(g, i) != NULL)
                {
                    printf("\nPage_rank cua %d la: %lf", i, page_rank[i]);
                }
            }
            break;
        case 3:
            printf("---Menu 3---");
            int m;
            printf("\nNhap so lan lap cua page rank:");
            scanf("%d", &m);
            for (int k = 0; k < m; k++)
            {
                for (int i = 0; i < 10000; i++)
                {
                    if (getVertex(g, i) != NULL)
                    {
                        temp1 = indegree(g, i, output1);
                        page_rank_temp[i] = 0;
                        for (int j = 0; j < temp1; j++)
                        {
                            temp2 = outdegree(g, output1[j], output2);
                            page_rank_temp[i] += (double)(page_rank[output1[j]] / temp2);
                        }
                    }
                }
                for (int i = 0; i < 10000; i++)
                {
                    if (page_rank_temp[i] > 0)
                        page_rank[i] = page_rank_temp[i];
                }
            }
            for (int i = 0; i < 10000; i++)
            {
                if (getVertex(g, i) != NULL)
                {
                    printf("\nPage_rank cua %d la: %lf", i, page_rank[i]);
                }
            }
            break;
        case 4:
            printf("\n---Menu 4---");
            count1 = 0;
            count2 = 0;
            jrb_traverse(ptr, g->vertices)
            {
                temp1 = jval_i(ptr->key); //lay id cua dinh
                temp2 = indegree(g, temp1, indeg1);
                temp3 = outdegree(g, temp1, outdeg1);
                printf("\n%d %d %d", temp1, temp2, temp3);
                if (temp2 > 0 && temp3 == 0)
                    count1++;
                if (temp2 == 0 && temp3 > 0)
                    count2++;
            }
            printf("\nSo luong webpages chi co lien ket den ma khong co lien ket ngoai la:%d", count1);
            printf("\nSo luong webpages chi co lien ket ngoai ma khong co lien ket den la:%d", count2);
            break;
        case 5:
            printf("\n---Menu 5---");
            printf("\n Nhap id1:");
            scanf("%d", &id1);
            if(getVertex(g,id1)==NULL){
                printf("\nKhong co webpage id %d trong do thi",id1);
                break;
            }
            printf("\n Nhap id2:");
            scanf("%d", &id2);
            if(getVertex(g,id2)==NULL){
                printf("\nKhong co webpage id %d trong do thi",id2);
                break;
            }
            int path[100], length;
            double test = shortestPath(g, id1, id2, path, &length);
            if (test == INFINITIVE_VALUE)
            {
                printf("\nKhong co lien ket nao tu %d toi %d", id1, id2);
            }
            else
            {
                printf("\nLien ket ngan nhat tu %d toi %d (co tong quang duong %.0lf):\n", id1, id2, test);
                for (int i = 0; i < length; i++)
                    printf("=> %d", path[i]);
            }
            break;
        case 6:
            printf("\n--Dang thoat chuong trinh--");
            dropGraph(g);
            exit(0);
            break;
        }
    }
    return 0;
}
