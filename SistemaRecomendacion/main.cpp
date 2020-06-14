#include <iostream>
#include "preprocesar.cpp"
#include "recommend.cpp"

using namespace std;

int main(){

	/*Preprocesamiento de la data
	 */
	//DataPreprocessing data("bandas.csv");
	//data.DataRecognition();
	//data.DataCleaning();
	
	/*sistema de recomendacion
	 */
	Recommender data;

	//data.loadData("ml-25m/ratings.csv");
	//cout<<data.computeSimilarity("Star Wars","Jaws");
	//data.loadData("Movie_Ratings.csv");
	data.loadData("datasetSmall/ratings.csv");
	//data.loadData("ml-latest/ratings.csv");
	//data.loadData("bandas.csv");
	//std::cout<<data.user.size()<<" "<<data.object.size();

	//cout<<data.computeSimilarity("You Got Mail","The Matrix");
	//cout<<data.computeSimilarity("Deadmau5","Slightly Stoopid");
	//cout<<data.computeSimilarity("2344","457")<<"\n";
	data.generateMatrix();
	//cout<<data.computeSimilarity("Alien","Avatar");
	//auto p=data.user.find("Stephen");
	//auto q=data.user.find("Amy");
	//cout<<jaccard(data.dualhash[p->second],
	//		data.dualhash[q->second]);
//	data.dualhash.show();	
	//auto v =data.influences("332",3);

	//cout<<data.recommender(v,"21")<<"\n";
	

	return 0;
}
