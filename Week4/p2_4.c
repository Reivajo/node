int mainCleanUp (int ret_value, Graph *gc, Node *out, Node *in, FILE *pf) {
    node_destroy(out);
    node_destroy(in);
    graph_destroy (gc);   
    fclose (pf);
    exit (ret_value);
}
