#include "pch.h"
#include <regex>

namespace gl
{
    namespace test
    {
        TEST(GraphLibTest, GraphInstance)
        {
            gl::Graph g1;
            gl::Node n1(g1);
            {
                gl::Graph g2;
                gl::Node n2(g2);
            }
        }

        TEST(GraphLibTest, NodeInstance)
        {
            gl::Graph g;

            {
                gl::Node e(g);
                EXPECT_EQ(g.nodes().size(), 1);
            }
            EXPECT_EQ(g.nodes().size(), 0);
        }

        TEST(GraphLibTest, EdgeInstance)
        {
            gl::Graph g;

            gl::Node n1(g);
            gl::Node n2(g);

            {
                gl::Edge e(g, n1, n2);
                EXPECT_EQ(g.edges().size(), 1);
            }
            EXPECT_EQ(g.edges().size(), 0);
        }

        // Test dynamically allocated Edges
        TEST(GraphLibTest, DynEdgeInstance)
        {
            gl::Graph* pg = new gl::Graph;

            gl::Node* pn1 = new gl::Node(*pg);
            gl::Node* pn2 = new gl::Node(*pg);

            {
                gl::Edge* pe = new gl::Edge(*pg, *pn1, *pn2);
                EXPECT_EQ(pg->edges().size(), 1);
                EXPECT_EQ(pg->nodes().size(), 2);
            }
            EXPECT_EQ(pg->edges().size(), 1);
            EXPECT_EQ(pg->nodes().size(), 2);
            delete pn2;
            EXPECT_EQ(pg->edges().size(), 0);
            EXPECT_EQ(pg->nodes().size(), 1);
            delete pg;
        }

        // Test Edges connected to different Graph than its Nodes

        TEST(Graph, findEdges)
        {
            Graph g1, g2;
            Node n1(g1), n2(g1), n3(g1);
            Node n4(g2);
            Edge e12a(g1, n1, n2), e12b(g1, n1, n2), e31(g1, n3, n1), e13(g1, n1, n3);

            try
            {
                EXPECT_EQ(g1.findEdges(n1, n2).size(), 2);
                EXPECT_EQ(g1.findEdges(n1, n3).size(), 1);
                EXPECT_EQ(g1.findEdges(n3, n1).size(), 1);
                EXPECT_EQ(g1.findEdges(n2, n3).size(), 0);
                g1.findEdges(n1, n4);
            }
            catch (const GraphLibException& e)
            {
                EXPECT_EQ(strcmp(e.what(), "Graph::findEdges: Nodes located in different Graphs."), 0);
            }
        }

        TEST(Graph, findNode)
        {
            Graph g1;
            Node n1(g1, "A"), n2(g1, "B");

            EXPECT_EQ(g1.findNode("A"), &n1);
            EXPECT_EQ(g1.findNode("B"), &n2);
            EXPECT_EQ(g1.findNode("C"), nullptr);
        }

        TEST(Graph, dijkstra_plain)
        {
            Graph g1;
            Node n1(g1), n2(g1), n3(g1), n4(g1), n5(g1);
            Edge e12a(g1, n1, n2), e12b(g1, n1, n2), e31(g1, n3, n1), e13(g1, n1, n3);
            Edge e23(g1, n2, n3), e24(g1, n2, n4), e43(g1, n4, n3), e41(g1, n4, n1), e51(g1, n5, n1);

            EXPECT_EQ(g1.dijkstra(n1, n4).size(), 2);
            EXPECT_EQ(g1.dijkstra(n4, n2).size(), 2);
            EXPECT_EQ(g1.dijkstra(n5, n4).size(), 3);
            EXPECT_EQ(g1.dijkstra(n1, n5).size(), 0);
        }

        TEST(Graph, dijkstra_override)
        {
            class NewEdge : public Edge
            {
            public:
                NewEdge(Graph& g, Node& src, Node& dst, double distance) : Edge(g, src, dst), m_distance(distance)
                {}

                virtual double weight() const override { return m_distance; }

            private:
                const double m_distance;
            };

            Graph g1;
            Node n1(g1), n2(g1), n3(g1), n4(g1), n5(g1);
            NewEdge e12a(g1, n1, n2, 1.0), e12b(g1, n1, n2, 1.0), e31(g1, n3, n1, 1.0), e13(g1, n1, n3, 1.0);
            NewEdge e23(g1, n2, n3, 1.0), e24(g1, n2, n4, 1.0), e43(g1, n4, n3, 1.0), e41(g1, n4, n1, 100.0), e51(g1, n5, n1, 1.0);

            EXPECT_EQ(g1.dijkstra(n1, n4).size(), 2);
            EXPECT_EQ(g1.dijkstra(n4, n2).size(), 3);
            EXPECT_EQ(g1.dijkstra(n5, n4).size(), 3);
            EXPECT_EQ(g1.dijkstra(n1, n5).size(), 0);
        }

        TEST(Node, name)
        {
            Graph g1;

            // check that auto-naming works
            class NewNode : public Node
            {
            public:
                NewNode(Graph& g) : Node(g) {}
                using Node::s_instance_number;
            };

            NewNode n11(g1);
            std::string name = n11.name();
            std::string number_s = std::regex_replace(
                    name,
                    std::regex("[^0-9]*([0-9]+).*"),
                    std::string("$1")
            );
            std::stringstream number_ss(number_s);
            int number_i;
            number_ss >> number_i;
            EXPECT_EQ(number_i, NewNode::s_instance_number);

            // check that the specific naming works
            Node n2(g1, "A");
            EXPECT_EQ(n2.name(), "A");
            try
            {
                Node n3(g1, "A");
            }
            catch (const GraphLibException& e)
            {
                EXPECT_EQ(strcmp(e.what(), "Node constructor: Node name is not unique"), 0);
            }
        }

        TEST(Edge, isConnectedTo)
        {
            Graph g1, g2;
            Node n1(g1), n2(g1), n3(g1), n4(g1), n5(g2);
            Edge e12a(g1, n1, n2), e12b(g1, n1, n2), e21(g1, n2, n1), e13(g1, n1, n3);

            EXPECT_TRUE(e12a.isConnectedTo(n1));
            EXPECT_TRUE(e12a.isConnectedTo(n2));
            EXPECT_FALSE(e12a.isConnectedTo(n3));
            EXPECT_FALSE(e12a.isConnectedTo(n4));
            EXPECT_FALSE(e12a.isConnectedTo(n5));
            EXPECT_TRUE(e12b.isConnectedTo(n1));
            EXPECT_TRUE(e21.isConnectedTo(n1));
            EXPECT_TRUE(e13.isConnectedTo(n1));
        }

        TEST(Edge, source)
        {
            Graph g1;
            Node n1(g1), n2(g1), n3(g1);
            Edge e12a(g1, n1, n2), e12b(g1, n1, n2), e21(g1, n2, n1), e13(g1, n1, n3);

            EXPECT_EQ(e12a.source(), n1);
            EXPECT_EQ(e12a.source(), n1);
            EXPECT_EQ(e21.source(), n2);
            EXPECT_EQ(e13.source(), n1);
        }

        TEST(Edge, destination)
        {
            Graph g1;
            Node n1(g1), n2(g1), n3(g1);
            Edge e12a(g1, n1, n2), e12b(g1, n1, n2), e21(g1, n2, n1), e13(g1, n1, n3);

            EXPECT_EQ(e12a.destination(), n2);
            EXPECT_EQ(e12a.destination(), n2);
            EXPECT_EQ(e21.destination(), n1);
            EXPECT_EQ(e13.destination(), n3);
        }
    }
}