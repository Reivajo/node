status queue_concatenate(q1,q2){
	int size1=0;
	int size2=0;
	int move=0;
	element x;

	size1=que_size(q1);
	size2=que_size(q2);
	while(queue_isEmpty(q2)==TRUE){
		x=queue_pop(q2);
		if(queu_push(q1,x)==ERROR){
			for(i=1;i<size1;i++){
				queue_push(q1,queue_pop(q1));
			}
			for(i=1;i<moved;i++){

				z=queue_pop(q1);
				queue_push(q2,z);
				elementfree(z);
			}
			queuepush(q2,x);
			for(i=1;i<size2s)
		}
	

	}
}