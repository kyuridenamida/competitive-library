for i in `ls cpp/include/*/* cpp/src/*`
do
    DOC="docs/`dirname $i`/`basename $i .cpp`.md"
    REPO="{{ site.github.repository_url }}/blob/master/$i"
    TOP="`realpath --relative-to="$i" cpp`"
    mkdir -p "docs/`dirname $i`"

    echo "## `basename $i`"    >  $DOC
    echo ""                    >> $DOC
    echo "- [GitHub]($REPO)"   >> $DOC
    echo ""                    >> $DOC

    INCLUDE=`cat $i | sed '/^#include.*util.h/d' |
        sed -n '/^#include.*\"/p' | cut -d"\"" -f2`
    if [ "$INCLUDE" != "" ]; then
        echo "### Include"         >> $DOC
        echo ""                    >> $DOC
        for FILENAME in $INCLUDE
        do
            echo -n "- [`basename $FILENAME`]" >> $DOC
            echo "(`dirname $FILENAME`/`basename $FILENAME .cpp`)" >> $DOC
        done
        echo ""                    >> $DOC
    fi
    echo "{% highlight cpp %}" >> $DOC
    cat $i | sed '/^#pragma/d' | sed '/^#include.*util.h/d' | sed '/./,$!d' >> $DOC
    echo "{% endhighlight %}"  >> $DOC
    echo ""                    >> $DOC
    echo "- [Back]($TOP)"      >> $DOC
done
