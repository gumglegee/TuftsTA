#!/usr/bin/perl

$| = 1;
#print "Content Type: text/plain\n\n";
#print "testOutput\n";
#print $ENV{'SCRIPT_FILENAME'};
#print "I am running in ", `pwd`, " with id " , `id`,"\n";

    local ($buffer, @pairs, $pair, $name, $value, %FORM);
    # Read in text
    $ENV{'REQUEST_METHOD'} =~ tr/a-z/A-Z/;
    if ($ENV{'REQUEST_METHOD'} eq "POST")
    {
        read(STDIN, $buffer, $ENV{'CONTENT_LENGTH'});
    }else {
	$buffer = $ENV{'QUERY_STRING'};
    }
    # Split information into name/value pairs
    @pairs = split(/&/, $buffer);
    foreach $pair (@pairs)
    {
	($name, $value) = split(/=/, $pair);
	$value =~ tr/+/ /;
	$value =~ s/%(..)/pack("C", hex($1))/eg;
	$FORM{$name} = $value;
    }
    if( $FORM{'word'} ){
        $word=$FORM{'word'};
    }
    
    if ( $FORM{'function'} ){
        $function=$FORM{'function'};
    }
    
    if ( $FORM{'currentTrie'} ){
        $currentTrie=$FORM{'currentTrie'};
    }

@ourPath = split(/\//, $ENV{'SCRIPT_FILENAME'});
# this array looks like
#  "h" "fred" "public_html", "foodir", "blah.pl"
# we want to pop off the last one
# 
$junk = pop(@ourPath);
#
# now ourPath has all but the last component
# 
$newpath = join("/", @ourPath);
$cmd = "$newpath/trie \"$word\" \"$function\" \"$currentTrie\"";

#print "About to run -- $cmd --\n";
$result = `$cmd`;
print "$result";

