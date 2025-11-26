int rank(db b[][100], int m, int n){
	int i,j,k,r,cnt=0;
	for (i=0;i<m;++i){
	    k=-1;
	    for (j=i;j<m;++j){
	        if (b[j][i]!=0){
	            k=j;
	            break;
	        }
	    }
	    if (k==-1) continue;
	    if (k!=i){
	        for (j=0;j<n;++j){
	            swap(&b[i][j],&b[k][j]);
	        }
	    }
	    for (r=i+1;r<m;++r){
	        db x=-b[r][i]/b[i][i];
	        int c;
	        for (c=0;c<n;++c){
	            b[r][c]+=x*b[i][c];
	        }
	    }
	}
	for (i=0;i<m;++i){
	    for (j=0;j<n;++j){
	        if (b[i][j]!=0){
	            ++cnt;
	            break;
	        }
	    }
	}
	return cnt;
}
