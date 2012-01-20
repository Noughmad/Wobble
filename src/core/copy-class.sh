OLD=Type
NEW=Variable

OLD_L=`echo ${OLD} | tr [A-Z] [a-z]`
OLD_U=`echo ${OLD} | tr [a-z] [A-Z]`

NEW_L=`echo ${NEW} | tr [A-Z] [a-z]`
NEW_U=`echo ${NEW} | tr [a-z] [A-Z]`

for ext in ".h" "_p.h" ".cpp"
do
    cat ${OLD_L}${ext} | sed -e "s/${OLD}/${NEW}/g" | sed -e "s/${OLD_U}/${NEW_U}/g" | sed -e "s/${OLD_L}/${NEW_L}/g" > ${NEW_L}${ext}
done
