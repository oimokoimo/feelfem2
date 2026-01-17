module UCD<src_file="ucd.f",build_dir="src",needs_obj="fld"> {
   fmethod+req update(
      .start+read+notify,.stop+read+write+notify,.step+read+write+notify,
      .filename+read+notify+req,.param+read+notify,.output+write
   ) = "method";
   boolean start<export=2,NEportLevels={2,0}>;
   boolean stop<export=2,NEportLevels={2,0}>;
   int step<export=2,NEportLevels={2,0}>; 
   string filename<export=2,NEportLevels={2,0}>;
   float param<export=2,NEportLevels={2,0}>;
   Field output;
};
